// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"


Plains::Plains() = default;

Plains::~Plains() = default;

StatusType Plains::add_team(int teamId)
{
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<teamNode> team = teams_table.find(teamId);
    if (team != nullptr){
        return StatusType::FAILURE;
    }

    try{
        team = std::make_shared<teamNode>(teamId);
        teams_table.insert(teamId, team);
        std::shared_ptr<ActiveTeam> activeTeam = std::make_shared<ActiveTeam>(teamId, team);
        active_teams_table.insert(teamId, activeTeam);
    }
    catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::add_jockey(int jockeyId, int teamId)
{
    if (teamId <= 0 || jockeyId <= 0){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Jockey> jockey = jockeys.find(jockeyId);
    std::shared_ptr<ActiveTeam> team = active_teams_table.find(teamId);
    if (jockey != nullptr || team == nullptr){
        return StatusType::FAILURE;
    }

    try{
        jockey = std::make_shared<Jockey>(jockeyId, teamId);
        jockeys.insert(jockeyId, jockey);
    }
    catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId)
{
    if (victoriousJockeyId <=0 || losingJockeyId <= 0 ||
        victoriousJockeyId == losingJockeyId){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Jockey> winner = jockeys.find(victoriousJockeyId);
    std::shared_ptr<Jockey> loser = jockeys.find(losingJockeyId);
    if (winner == nullptr || loser == nullptr){
        return StatusType::FAILURE;
    }

    std::shared_ptr<ActiveTeam> winningTeam = Find(winner->getTeam());
    std::shared_ptr<ActiveTeam> losingTeam = Find(loser->getTeam());
    if (winningTeam == losingTeam){
        return StatusType::FAILURE;
    }

    if (winningTeam->getRecord() != 0){
        records.remove(winningTeam->getRecord(), winningTeam->getID());
    }

    if (losingTeam->getRecord() != 0){
        records.remove(losingTeam->getRecord(), losingTeam->getID());
    }

    winner->setRecord(winner->getRecord()+1);
    loser->setRecord(loser->getRecord()-1);
    winningTeam->setRecord(winningTeam->getRecord()+1);
    losingTeam->setRecord(losingTeam->getRecord()-1);

    if (winningTeam->getRecord() != 0) {
        try{
            std::shared_ptr<Record> winnerRecord = std::make_shared<Record>(winningTeam->getRecord(), winningTeam->getID());
            records.insert(winnerRecord->getRecord(), winnerRecord, winningTeam->getID());
        }
        catch (std::bad_alloc &) {
            return StatusType::ALLOCATION_ERROR;
        }
    }
    if (losingTeam->getRecord() != 0) {
        try{
            std::shared_ptr<Record> loserRecord = std::make_shared<Record>(losingTeam->getRecord(), losingTeam->getID());
            records.insert(loserRecord->getRecord(), loserRecord, losingTeam->getID());
        }
        catch (std::bad_alloc &) {
            return StatusType::ALLOCATION_ERROR;
        }
    }

    return StatusType::SUCCESS;

}

StatusType Plains::merge_teams(int teamId1, int teamId2)
{
    if (teamId1 <=0 || teamId2 <= 0 ||
        teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<ActiveTeam> mergedTeam = Union(teamId1, teamId2);
    if (mergedTeam == nullptr){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::unite_by_record(int record)
{
    if (record <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (!records.canUnitedByRecord(record)){
        return StatusType::FAILURE;
    }
    int team1 = records.getTeamByRecord(record);
    int team2 = records.getTeamByRecord(-record);

    merge_teams(team1, team2);
    return StatusType::SUCCESS;
}

output_t<int> Plains::get_jockey_record(int jockeyId)
{
    if (jockeyId <= 0){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Jockey> jockey = jockeys.find(jockeyId);
    if (jockey == nullptr){
        return {StatusType::FAILURE};
    }
    return jockey->getRecord();
}

output_t<int> Plains::get_team_record(int teamId)
{
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<ActiveTeam> team = active_teams_table.find(teamId);
    if (team == nullptr){
        return {StatusType::FAILURE};
    }
    return team->getRecord();
}

std::shared_ptr<ActiveTeam> Plains::Union(int team1, int team2){
    std::shared_ptr<ActiveTeam> activeTeam1 = active_teams_table.find(team1);
    std::shared_ptr<ActiveTeam> activeTeam2 = active_teams_table.find(team2);
    if(!activeTeam1 || !activeTeam2){
        return nullptr;
    }

    int newRecord = activeTeam1->getRecord() + activeTeam2->getRecord();
    int newSize = activeTeam1->getSize() + activeTeam2->getSize();

    std::shared_ptr<ActiveTeam> bigTeam = activeTeam1->getSize() >= activeTeam2->getSize() ?
                          activeTeam1 : activeTeam2;
    std::shared_ptr<ActiveTeam> smallTeam = activeTeam1->getSize() < activeTeam2->getSize() ?
                            activeTeam1 : activeTeam2;

    std::shared_ptr<ActiveTeam> betterTeam = activeTeam1->getRecord() >= activeTeam2->getRecord() ?
                             activeTeam1 : activeTeam2;
    std::shared_ptr<ActiveTeam> worseTeam = activeTeam1->getRecord() < activeTeam2->getRecord() ?
                            activeTeam1 : activeTeam2;

    smallTeam->getRoot()->setParent(bigTeam->getRoot());

    if (bigTeam != betterTeam){
        betterTeam->setRoot(bigTeam->getRoot());
        bigTeam->getRoot()->setActiveTeam(betterTeam->getID());
    }

    records.remove(worseTeam->getRecord(), worseTeam->getID());
    active_teams_table.remove(worseTeam->getID());

    records.remove(betterTeam->getRecord(), betterTeam->getID());
    if (newRecord != 0){
        std::shared_ptr<Record> updatedRecord = std::make_shared<Record>(newRecord, betterTeam->getID());
        records.insert(newRecord, updatedRecord, betterTeam->getID());
    }
    betterTeam->setRecord(newRecord);
    betterTeam->setSize(newSize);
    return betterTeam;
}

std::shared_ptr<ActiveTeam> Plains::Find(int teamId){
    std::shared_ptr<teamNode> team = teams_table.find(teamId);
    if (team == nullptr){
        return nullptr;
    }
    std::shared_ptr<teamNode> current = team;
    while(current->getParent() != nullptr){
        current = current->getParent();
    }
    std::shared_ptr<teamNode> root = current;
    current = team;
    while (current != root){
        std::shared_ptr<teamNode> temp = current->getParent();
        current->setParent(root);
        current = temp;
    }
    return active_teams_table.find(root->getActiveTeam());
}
