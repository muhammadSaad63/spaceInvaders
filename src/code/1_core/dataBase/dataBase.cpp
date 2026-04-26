#include <cctype>
#include <filesystem>
#include "dataBase.hpp"
namespace fs = std::filesystem;


// helper functions
// void DataBase::createTable_players(){
//     db.exec(
//         "CREATE TABLE IF NOT EXISTS players" 
//         "("
//             "playerID INTEGER PRIMARY KEY AUTOINCREMENT,"
//             "playerName TEXT UNIQUE NOT NULL"
//         ")"
//     );
// }
void DataBase::createTable_games(){
    db.exec(
        "CREATE TABLE IF NOT EXISTS games"
        "("
            "gameID INTEGER PRIMARY KEY AUTOINCREMENT,"
            // "playerID INTEGER NOT NULL,"

            "score INTEGER NOT NULL DEFAULT 0,"                     // min poss value = 0
            "enemiesDefeated INTEGER NOT NULL DEFAULT 0,"           // min poss value = 0
            "waveReached INTEGER NOT NULL DEFAULT 1,"               // min poss value = 1

            "timePlayed REAL NOT NULL DEFAULT 0"

            // "FOREIGN KEY (playerID) REFERENCES players(playerID)"
        ")"
    );
}
// void DataBase::initTable_players(){
//     db.exec(
//         "INSERT OR IGNORE INTO players (playerID, playerName) VALUES " 
//             "('1', 'Ebbi'),"
//             "('2', 'Saad'),"
//             "('3', 'Umair')"
//     );
// }
// void DataBase::upperCaseStr(string& playerName){
//     for (auto& c : playerName){
//         if (std::isalpha(c) && std::islower(c)){
//             c = std::toupper(c);
//         }
//     }  
// }
// int DataBase::getNumUniquePlayersInGames(){
//     SQLite::Statement query(db, "SELECT COUNT( DISTINCT playerID ) FROM games");
//     query.executeStep();

//     return (query.getColumn(0).getInt());
// }
int DataBase::getTotalGames(){
    SQLite::Statement query(db, "SELECT COUNT(*) FROM games");
    query.executeStep();

    return (query.getColumn(0).getInt());
}

DataBase::DataBase()
: db((fs::create_directories("src/assets/data"), "src/assets/data/programData.db"), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    // creating table 'players' to store players' data
    // createTable_players();

    // creating table 'games' to store data about individual games
    createTable_games();

    // :>
    // initTable_players();
}

// writing/adding data
// void DataBase::addPlayer(string& playerName){
//     // uppercasing playerName
//     upperCaseStr(playerName);

//     SQLite::Statement query(db, "INSERT OR IGNORE INTO players (playerName) VALUES (?)");         // will only insert if the name does not already exist in players (due to defined schema); will ignore if it alr exists

//     query.bind(1, playerName);             // binding playerName to (the 1st & only) ?
//     query.exec();                          // executing the query
// }
void DataBase::addGame(GameData& gameData){
    SQLite::Statement query(db, "INSERT INTO games (score, enemiesDefeated, waveReached, timePlayed) VALUES (?, ?, ?, ?)");         

    // binding data from gameData to their respective ?
    query.bind(1, gameData.score);
    query.bind(2, gameData.enemiesDefeated);
    query.bind(3, gameData.waveReached);
    // query.bind(4, gameData.timeStarted);   
    // query.bind(5, gameData.timeEnded);   
    query.bind(4, gameData.timePlayed);             

    query.exec();                               // executing the query
}

// fetching/reading data
vector<GameData> DataBase::getHistory(int numEntries){
    vector<GameData> history;

    {                                                                       // y? dil cheh rha teh :>
        auto totalEntries = getTotalGames();
        numEntries = (totalEntries < numEntries)? totalEntries : numEntries;

        history.reserve(numEntries);
    }

    {
        SQLite::Statement query(db, 
                                    "SELECT gameID, score, enemiesDefeated, "
                                    "waveReached, timePlayed "
                                    "FROM games " 
                                    "ORDER BY gameID DESC LIMIT (?)"
                                );
        query.bind(1, numEntries);

        while (query.executeStep())
        {
            history.push_back(
                GameData{ 
                    query.getColumn(0).getInt(),                // gameID
                    // query.getColumn(1).getInt(),             // playerID
                    // query.getColumn(2).getString(),          // playerName
                    query.getColumn(1).getInt(),                // score
                    query.getColumn(2).getInt(),                // enemiesDefeated
                    query.getColumn(3).getInt(),                // waveReached
                    // query.getColumn(4).getString(),          // timeStarted
                    // query.getColumn(5).getString(),          // timeEnded
                    query.getColumn(4).getDouble(),             // timePlayed
                }
            );
        }
    }

    return history;
}
// vector<GameData> DataBase::getLeaderBoards(int numEntries){
    //     vector<GameData> leaderBoards;

//     {                                                                       // y? dil cheh rha teh :>
//         auto totalEntries = getNumUniquePlayersInGames();
//         numEntries = ((totalEntries < numEntries)? totalEntries : numEntries);

//         leaderBoards.reserve(numEntries);
//     }

//     {
//         SQLite::Statement query(db, 
//                                     "SELECT games.playerID, players.playerName, MAX(games.score) "
//                                     "FROM games "
//                                     "JOIN players ON games.playerID = players.playerID "
//                                     "GROUP BY playerID "
//                                     "ORDER BY Max(score) DESC "
//                                     "LIMIT (?)"
//                                 );
//         query.bind(1, numEntries);

//         while (query.executeStep())
//         {
//             leaderBoards.push_back(
//                 GameData{ 
//                     -1,                                     // gameID
//                     query.getColumn(0).getInt(),            // playerID
//                     query.getColumn(1).getString(),         // playerName
//                     query.getColumn(2).getInt(),            // score
//                     -1,                                     // enemiesDefeated
//                     -1,                                     // waveReached
//                     "N/A",                                  // timeStarted
//                     "N/A",                                  // timeEnded
//                     -1,                                     // timePlayed
//                 }
//             );
//         }
//     }

//     return leaderBoards;
// }

StatData DataBase::getStatistics(){
    SQLite::Statement query(db, 
                                "SELECT SUM(score), MAX(score), AVG(score)                              , "
                                "       SUM(enemiesDefeated), MAX(enemiesDefeated), AVG(enemiesDefeated), "
                                "       SUM(waveReached), MAX(waveReached), AVG(waveReached)            , "
                                "       SUM(timePlayed), MAX(timePlayed), AVG(timePlayed)                 "
                                "FROM games "
                            );

    StatData stats;

    if (query.executeStep()){
        // Score Statistics
        stats.totalScore                = query.getColumn(0).getInt();
        stats.maxScorePerGame           = query.getColumn(1).getInt();
        stats.avgScorePerGame           = query.getColumn(2).getInt();

        // Enemy Statistics
        stats.totalEnemiesDefeated      = query.getColumn(3).getInt();
        stats.maxEnemiesDefeatedPerGame = query.getColumn(4).getInt();
        stats.avgEnemiesDefeatedPerGame = query.getColumn(5).getInt();

        // Wave Statistics
        stats.totalWavesCleared         = query.getColumn(6).getInt();
        stats.maxWavesClearedPerGame    = query.getColumn(7).getInt();
        stats.avgWavesClearedPerGame    = query.getColumn(8).getInt();

        // Time Statistics
        stats.totalTimePlayed           = query.getColumn(9).getDouble();
        stats.maxTimePlayedPerGame      = query.getColumn(10).getDouble();
        stats.avgTimePlayedPerGame      = query.getColumn(11).getDouble();
    }

    return stats;
}