#include <cctype>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <SQLiteCpp.h>
#include "dataBase.hpp"
using std::string, std::vector;


class DataBase{
    private:
        SQLite::Database db;

        void createTable_players(){
            db.exec(
                "CREATE TABLE IF NOT EXISTS players" 
                "("
                    "playerID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "playerName TEXT UNIQUE NOT NULL"
                ")"
            );
        }
        void createTable_games(){
            db.exec(
                "CREATE TABLE IF NOT EXISTS games"
                "("
                    "gameID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "playerID INTEGER NOT NULL,"
                    
                    "score INTEGER NOT NULL DEFAULT 0,"                     // min poss value = 0
                    "enemiesDefeated INTEGER NOT NULL DEFAULT 0,"           // min poss value = 0
                    "waveReached INTEGER NOT NULL DEFAULT 1,"               // min poss value = 1
                    
                    "timeStarted DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,"          // Current_timestamp is a func which returns the timestamp when the row was written
                    "timeEnded DATETIME NOT NULL,"
                    "timePlayed INTEGER NOT NULL,"
        
                    "FOREIGN KEY (playerID) REFERENCES players(playerID)"
                ")"
            );
        }
        void initTable_players(){
            db.exec(
                "INSERT OR IGNORE INTO players (playerID, playerName) VALUES" 
                    "('1', 'Ebbi'),"
                    "('2', 'Saad'),"
                    "('3', 'Umair')"
            );
        }
        void upperCaseStr(string& playerName){
            for (auto& c : playerName){
                if (std::isalpha(c) && std::islower(c)){
                    c = std::toupper(c);
                }
            }  
        }
        int getNumUniquePlayersInGames(){
            SQLite::Statement query(db, "SELECT COUNT( DISTINCT playerID ) FROM games");
            query.executeStep();

            return (query.getColumn(0).getInt());
        }
        int getTotalGames(){
            SQLite::Statement query(db, "SELECT COUNT(*) FROM games");
            query.executeStep();

            return (query.getColumn(0).getInt());
        }

    public:
        DataBase()
        : db("assets/data/programData.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
        {
            // creating table 'players' to store players' data
            createTable_players();

            // creating table 'games' to store data about individual games
            createTable_games();

            // :>
            initTable_players();
        }

        // writing/adding data
        void addPlayer(string& playerName){
            // uppercasing playerName
            upperCaseStr(playerName);

            SQLite::Statement query(db, "INSERT OR IGNORE INTO players (playerName) VALUES (?)");         // will only insert if the name does not already exist in players (due to defined schema); will ignore if it alr exists

            query.bind(1, playerName);             // binding playerName to (the 1st & only) ?
            query.exec();                          // executing the query
        }
        void addGame(GameData& gameData){
            SQLite::Statement query(db, "INSERT INTO games (playerID, score, enemiesDefeated, waveReached, timeEnded, timePlayed) VALUES (?, ?, ?, ?, ?, ?)");         

            // binding data from gameData to their respective ?
            query.bind(1, gameData.playerID);
            query.bind(2, gameData.score);
            query.bind(3, gameData.enemiesDefeated);
            query.bind(4, gameData.waveReached);
            query.bind(5, 2);   
            query.bind(6, gameData.timePlayed);             

            query.exec();                               // executing the query
        }
        
        // fetching/reading data
        vector<GameData> getHistory(int numEntries){
            vector<GameData> history;

            {                                                                       // y? dil cheh rha teh :>
                auto totalEntries = getTotalGames();
                numEntries = (totalEntries < numEntries)? totalEntries : numEntries;

                history.reserve(numEntries);
            }


            {
                SQLite::Statement query(db, 
                                            "SELECT g.gameID, g.playerID, p.playerName, g.score, g.enemiesDefeated,"
                                            "g.waveReached, g.timeStarted, g.timeEnded, g.timePlayed "
                                            "FROM games AS g"
                                            "JOIN players AS p ON g.playerID = p.playerID"
                                            "ORDER BY g.gameID DESC LIMIT (?)"
                                        );
                query.bind(1, numEntries);

                while (query.executeStep())
                {
                    history.push_back(
                        GameData{ 
                            query.getColumn(0).getInt(),            // gameID
                            query.getColumn(1).getInt(),            // playerID
                            query.getColumn(2).getString(),         // playerName
                            query.getColumn(3).getInt(),            // score
                            query.getColumn(4).getInt(),            // enemiesDefeated
                            query.getColumn(5).getInt(),            // waveReached
                            query.getColumn(6).getString(),         // timeStarted
                            query.getColumn(7).getString(),         // timeEnded
                            query.getColumn(8).getInt(),            // timePlayed
                        }
                    );
                }
            }

            return history;
        }
        vector<GameData> getLeaderBoards(int numEntries){
            vector<GameData> leaderBoards;

            {                                                                       // y? dil cheh rha teh :>
                auto totalEntries = getNumUniquePlayersInGames();
                numEntries = ((totalEntries < numEntries)? totalEntries : numEntries);

                leaderBoards.reserve(numEntries);
            }

            {
                SQLite::Statement query(db, 
                                            "SELECT games.playerID, players.playerName, MAX(games.score)"
                                            "FROM games"
                                            "JOIN players ON games.playerID = players.playerID"
                                            "GROUP BY playerID"
                                            "ORDER BY Max(score) DESC"
                                            "LIMIT (?)"
                                        );
                query.bind(1, numEntries);

                while (query.executeStep())
                {
                    leaderBoards.push_back(
                        GameData{ 
                            -1,                                     // gameID
                            query.getColumn(0).getInt(),            // playerID
                            query.getColumn(1).getString(),         // playerName
                            query.getColumn(2).getInt(),            // score
                            -1,                                     // enemiesDefeated
                            -1,                                     // waveReached
                            "N/A",                                  // timeStarted
                            "N/A",                                  // timeEnded
                            -1,                                     // timePlayed
                        }
                    );
                }
            }

            return leaderBoards;
        }
};