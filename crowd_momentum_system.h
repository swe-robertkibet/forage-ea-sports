#ifndef CROWD_MOMENTUM_SYSTEM_H
#define CROWD_MOMENTUM_SYSTEM_H

#include <vector>
#include <string>
#include <memory>

// forward declarations to avoid any circular dependencies
class Team;
class Player;
class Coach;
class Stadium;
class Crowd;

// enume...
enum class EventType {
    TOUCHDOWN,
    INTERCEPTION,
    SACK,
    FOURTH_DOWN_STOP,
    FUMBLE,
    FIELD_GOAL,
    PENALTY,
    SAFETY,
    TURNOVER
};

enum class EffectType {
    REACTION_TIME_BOOST,
    ACCURACY_BOOST,
    BLOCKING_EFFICIENCY,
    SNAP_TIMING_PENALTY,
    FOCUS_REDUCTION,
    FALSE_START_INCREASE
};

enum class MomentumLevel {
    VERY_LOW,
    LOW,
    NEUTRAL,
    HIGH,
    VERY_HIGH
};

enum class VenueType {
    SMALL_STADIUM,
    MEDIUM_STADIUM,
    LARGE_STADIUM,
    DOME_STADIUM,
    OUTDOOR_STADIUM
};

enum class Position {
    QUARTERBACK,
    RUNNING_BACK,
    WIDE_RECEIVER,
    TIGHT_END,
    OFFENSIVE_LINE,
    DEFENSIVE_LINE,
    LINEBACKER,
    CORNERBACK,
    SAFETY,
    KICKER
};

// utility structures
struct PlayerStats {
    float speed;
    float accuracy;
    float strength;
    float awareness;
    float composure;
};

/**
 * main controller class for the Dynamic Crowd Momentum System
 * it orchestrates all momentum-related gameplay mechanics
 */
class CrowdMomentumSystem {
private:
    std::unique_ptr<MomentumMeter> momentum_meter;
    GameState* game_state;
    Stadium* stadium;
    bool system_enabled;
    float update_frequency;

public:
    // constructor and Destructor
    CrowdMomentumSystem(GameState* gameState, Stadium* stadium);
    ~CrowdMomentumSystem();

    // main system methods
    void initialize();
    void processGameEvent(const GameEvent& event);
    void updateMomentum(float delta_time);
    void applyMomentumEffects();
    void shutdown();

    // system control
    void enableSystem();
    void disableSystem();
    bool isSystemEnabled() const;

    // configuration
    void setUpdateFrequency(float frequency);
    float getUpdateFrequency() const;
};

/**
 * tracks and manages momentum levels for both teams
 */
class MomentumMeter {
private:
    float home_momentum;
    float away_momentum;
    float momentum_threshold;
    float momentum_decay_rate;
    float max_momentum;
    float min_momentum;

public:
    // constructor
    MomentumMeter(float threshold = 50.0f, float decayRate = 0.1f);

    // momentum management
    float getMomentum(const Team& team) const;
    void setMomentum(const Team& team, float value);
    void adjustMomentum(const Team& team, float adjustment);
    void decayMomentum(float delta_time);
    void resetMomentum();

    // momentum analysis
    MomentumLevel getMomentumLevel(const Team& team) const;
    float getMomentumDifference() const;
    bool isAtThreshold(const Team& team) const;

    // configuration
    void setThreshold(float threshold);
    void setDecayRate(float rate);
    float getThreshold() const;
    float getDecayRate() const;
};

/**
 * crowd's behavior and reactions during gameplay
 */
class Crowd {
private:
    float noise_level;
    float enthusiasm;
    Stadium* stadium;
    std::vector<std::unique_ptr<CrowdSection>> crowd_sections;
    float base_noise_level;
    float max_noise_level;

public:
    // constructor and Destructor
    Crowd(Stadium* stadium, int num_sections = 8);
    ~Crowd();

    // crowd reactions
    void reactToEvent(const GameEvent& event);
    void generateNoise();
    void updateEnthusiasm(float adjustment);
    void resetCrowd();

    // crowd state queries
    float getNoiseLevel() const;
    float getEnthusiasm() const;
    float getVolumeLevel() const;
    bool isQuiet() const;
    bool isLoud() const;

    // configuration
    void setBaseNoiseLevel(float level);
    void setMaxNoiseLevel(float level);
    void addCrowdSection(Team* team, int capacity);
};

/**
 * Individual section of the crowd with specific team affiliation
 */
class CrowdSection {
private:
    std::string section_id;
    Team* team_affiliation;
    int capacity;
    int current_attendance;
    float current_enthusiasm;
    float noise_contribution;

public:
    // constructor
    CrowdSection(const std::string& id, Team* team, int capacity);

    // section actions
    void cheer(float intensity = 1.0f);
    void boo(float intensity = 1.0f);
    void reactToPlay(const GameEvent& event);
    
    // sttate queries
    float getNoiseContribution() const;
    float getEnthusiasm() const;
    Team* getTeamAffiliation() const;
    int getCapacity() const;
    int getCurrentAttendance() const;

    // configuration
    void setAttendance(int attendance);
    void setEnthusiasm(float enthusiasm);
};

/**
 * this represents significant game events that trigger momentum changes
 */
class GameEvent {
private:
    EventType event_type;
    Team* team;
    Player* player;
    float momentum_impact;
    float timestamp;
    bool is_home_team_event;

public:
    // constructor
    GameEvent(EventType type, Team* team, Player* player = nullptr);

    // event properties
    EventType getEventType() const;
    Team* getTeam() const;
    Player* getPlayer() const;
    float getMomentumImpact() const;
    float getTimestamp() const;
    bool isHomeTeamEvent() const;

    // impact calculation
    void calculateMomentumImpact(const GameState& gameState);
    void setMomentumImpact(float impact);
};

/**
 * effects applied to players based on current momentum levels
 */
class MomentumEffect {
private:
    EffectType effect_type;
    float magnitude;
    float duration;
    float remaining_time;
    Team* target_team;
    bool is_positive_effect;

public:
    // constructor
    MomentumEffect(EffectType type, float magnitude, float duration, Team* team);

    // effect management
    void apply(Player& player);
    void remove(Player& player);
    void update(float delta_time);

    // effect queries
    bool isActive() const;
    float getEffectStrength() const;
    EffectType getEffectType() const;
    Team* getTargetTeam() const;
    bool isPositiveEffect() const;
    float getRemainingTime() const;
};

/**
 * individual player affected by momentum system
 */
class Player {
private:
    std::string player_id;
    std::string player_name;
    Team* team;
    Position position;
    PlayerStats base_stats;
    PlayerStats current_stats;
    std::vector<MomentumEffect*> current_effects;
    float composure_level;
    bool momentum_immune;

public:
    // constructor
    Player(const std::string& id, const std::string& name, Team* team, Position pos);

    // effect management
    void applyEffect(MomentumEffect* effect);
    void removeEffect(MomentumEffect* effect);
    void updateEffects(float delta_time);
    void clearAllEffects();

    // player queries
    PlayerStats getModifiedStats() const;
    PlayerStats getBaseStats() const;
    bool isAffectedByMomentum() const;
    float getComposureLevel() const;
    Position getPosition() const;
    Team* getTeam() const;
    std::string getName() const;

    //configuration
    void setComposureLevel(float level);
    void setMomentumImmune(bool immune);
    void setBaseStats(const PlayerStats& stats);
};

/**
 *team entity containing players and game state
 */
class Team {
private:
    std::string team_id;
    std::string team_name;
    bool is_home_team;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<Coach> coach;
    bool composure_mode_active;
    float team_morale;

public:
    //constructor and Destructor
    Team(const std::string& id, const std::string& name, bool isHome);
    ~Team();

    //player management
    void addPlayer(std::unique_ptr<Player> player);
    void removePlayer(const std::string& player_id);
    std::vector<Player*> getPlayers() const;
    Player* getPlayer(const std::string& player_id) const;

    //  team properties
    bool isHomeTeam() const;
    std::string getName() const;
    std::string getId() const;
    Coach* getCoach() const;

    // composure mode
    void activateComposureMode();
    void deactivateComposureMode();
    bool isComposureModeActive() const;

    // team state
    void setMorale(float morale);
    float getMorale() const;
    void setCoach(std::unique_ptr<Coach> coach);
};

/**
 * coach who can activate team composure mode
 */
class Coach {
private:
    std::string coach_id;
    std::string coach_name;
    Team* team;
    int leadership_rating;
    float composure_cooldown;
    float cooldown_remaining;
    bool can_use_composure;

public:
    // constructor
    Coach(const std::string& id, const std::string& name, Team* team, int leadership);

    // Composure management
    bool canActivateComposure() const;
    void activateTeamComposure();
    void updateCooldown(float delta_time);
    void resetCooldown();

    // coach properties
    float getLeadershipBonus() const;
    int getLeadershipRating() const;
    Team* getTeam() const;
    std::string getName() const;
    float getCooldownRemaining() const;

    // configuration
    void setLeadershipRating(int rating);
    void setCooldownTime(float cooldown);
};

/**
 * stadium containing crowd and venue information
 */
class Stadium {
private:
    std::string stadium_id;
    std::string stadium_name;
    int capacity;
    std::unique_ptr<Crowd> crowd;
    VenueType venue_type;
    float rivalry_factor;
    float home_field_advantage;

public:
    // constructor and Destructor
    Stadium(const std::string& id, const std::string& name, int capacity, VenueType type);
    ~Stadium();

    // stadium properties
    Crowd* getCrowd() const;
    int getCapacity() const;
    VenueType getVenueType() const;
    std::string getName() const;
    std::string getId() const;

    // game modifiers
    float getRivalryMultiplier() const;
    float getVenueBonus() const;
    float getHomeFieldAdvantage() const;

    // configuration
    void setRivalryFactor(float factor);
    void setHomeFieldAdvantage(float advantage);
    void initializeCrowd(Team* homeTeam, Team* awayTeam);
};

/**
 * current game state information
 */
class GameState {
private:
    int current_quarter;
    int time_remaining;
    int home_score;
    int away_score;
    Team* home_team;
    Team* away_team;
    bool is_rivalry_game;
    bool is_playoff_game;
    float game_tension;

public:
    // constructor
    GameState(Team* homeTeam, Team* awayTeam);

    // time management
    int getCurrentQuarter() const;
    int getTimeRemaining() const;
    void setTime(int quarter, int time);
    void updateTime(int seconds);

    // score management
    int getHomeScore() const;
    int getAwayScore() const;
    int getScoreDifference() const;
    void updateScore(Team* team, int points);

    // game analysis
    bool isLateGame() const;
    bool isCloseGame() const;
    bool isRivalryGame() const;
    bool isPlayoffGame() const;
    float getGameTension() const;

    // team access
    Team* getHomeTeam() const;
    Team* getAwayTeam() const;

    // configuration
    void setRivalryStatus(bool isRivalry);
    void setPlayoffStatus(bool isPlayoff);
    void calculateGameTension();
};

/**
 *team composure mode for mitigating crowd effects
 */
class TeamComposureMode {
private:
    bool is_active;
    float duration;
    float remaining_time;
    float effectiveness;
    float cooldown_time;
    float cooldown_remaining;
    Coach* activating_coach;

public:
    // constructor
    TeamComposureMode(float duration = 30.0f, float effectiveness = 0.7f);

    // mode control
    void activate(Coach* coach);
    void deactivate();
    void update(float delta_time);

    // mode queries
    bool isActive() const;
    float getMitigationFactor() const;
    float getRemainingTime() const;
    float getCooldownRemaining() const;
    bool canActivate() const;

    //configuration
    void setDuration(float duration);
    void setEffectiveness(float effectiveness);
    void setCooldownTime(float cooldown);
};

#endif