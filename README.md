# Dynamic Crowd Momentum System

## Overview

The Dynamic Crowd Momentum System introduces a feature where the energy and reactions of the in-game crowd directly influence player performance on the field. College football is known for its electrifying atmospheres, and this system would bring that realism into the game by simulating how fans can inspire players to perform better, or rattle them under pressure.

## Value Statement

College football thrives on pageantry, passion, and intense fan engagement. Capturing this emotional intensity would significantly deepen immersion for players. With this system, fans don't just exist as background visuals but as an active force within gameplay. The feature highlights the unique culture of college football stadiums while adding a new strategic element for both players and coaches in-game. This would encourage gamers to not only master plays but also manage game momentum, making every match more unpredictable and rewarding.

## Solution

The system would integrate with existing player stamina, confidence, and fatigue mechanics. Crowd momentum is represented by a "Momentum Meter" that shifts based on big plays (touchdowns, interceptions, sacks, fourth-down stops). A home team with a high momentum meter might receive boosts such as slightly faster reaction times, improved accuracy for quarterbacks, or better blocking efficiency. Conversely, the away team might experience penalties such as delayed snap timing, reduced receiver focus, or increased chance of a false start. Crowd behavior would be dynamic, cheering louder for rivalries or late-game comebacks, and quieting down if their team struggles. To keep the system balanced, boosts and penalties would be modest, ensuring they enhance realism without overshadowing player skill. Players could also activate "Team Composure Mode," where strong leadership (from a quarterback or coach) mitigates crowd impact during high-pressure moments.

## Evaluation Statement

The Dynamic Crowd Momentum System adds excitement, unpredictability, and authenticity to gameplay. Benefits include greater immersion, deeper strategic play, and better representation of the college football atmosphere. Risks include potential frustration for players who feel disadvantaged as the away team. To address this, the system would be optional (toggleable in settings) and carefully tuned so no momentum swing is overwhelming. Additionally, the boosts would remain subtle, rewarding skillful play rather than replacing it. By transforming the crowd from a background element into an interactive gameplay factor, this feature would deliver a more authentic and thrilling college football experience that mirrors the heart and soul of the sport.

## Task 2: Class Diagram Design

### Task Overview

Following the successful feature proposal, we moved into the technical design phase using object-oriented programming principles. This task involved creating a comprehensive class diagram to visualize the system architecture before implementation.

**What we learned:**

- How to translate feature requirements into object-oriented design
- Creating class diagrams to visualize system relationships
- Applying design patterns and SOLID principles
- Planning system architecture before coding

### Object-Oriented Design Process

The Dynamic Crowd Momentum System required breaking down the feature into a collection of interacting objects. Using C++ as our target language, we needed to design classes that would handle crowd behavior, momentum tracking, player effects, and game state management.

The design process focused on:

- **High-level relationships** between system components
- **Interface design** for how classes interact with each other
- **Data encapsulation** and responsibility separation
- **Extensibility** for future feature additions

### Class Diagram

The complete system architecture is documented in `class-diagram.png`, which shows the relationships between all major components of the Dynamic Crowd Momentum System.

#### Key System Components

**Core System Classes:**

- `CrowdMomentumSystem`: Main controller that orchestrates all momentum-related functionality
- `MomentumMeter`: Tracks and manages momentum levels for both teams
- `GameState`: Maintains current game information (quarter, score, time, etc.)

**Crowd Simulation:**

- `Crowd`: Represents overall crowd behavior and noise generation
- `CrowdSection`: Individual crowd sections with team affiliations
- `Stadium`: Contains crowd and venue-specific information

**Game Entities:**

- `Player`: Individual players affected by momentum changes
- `Team`: Team entities with roster and composure management
- `Coach`: Leadership role capable of activating composure mode

**Effect System:**

- `GameEvent`: Triggers for momentum changes (touchdowns, interceptions, etc.)
- `MomentumEffect`: Applied effects that modify player performance
- `TeamComposureMode`: System for mitigating negative crowd effects

### System Architecture Benefits

The class diagram reveals a well-structured system with clear separation of concerns:

- **Modular Design**: Each class has specific responsibilities
- **Composition over Inheritance**: Complex behaviors built from simpler components
- **Event-Driven Architecture**: GameEvents trigger system responses
- **Strategy Pattern**: Different effect types and crowd behaviors
- **State Management**: Clear tracking of game and momentum states

## Task 4: Live Bugfix

### Task Overview

As part of the EA Sports College Football development team, we were tasked with fixing a critical bug in the live inventory system. This task involved creating a patch for an existing game file and optimizing code in a collaborative game development environment.

**What we learned:**

- How to create a patch for a change to an existing game file
- How to optimize code in a collaborative game development environment
- Using vectors instead of C-style arrays to optimize the codebase

### The Problem (Yellow Ticket)

The current version of the inventory system in `task-4-starter.cpp` did not fully implement item removal. When items were "removed" from the inventory, they were left in the item list with a quantity of 0, creating "ghost" entries. This was impacting live customers who expected items to be completely removed from their inventories.

**Key Issues Identified:**

- Items with 0 quantity remained as ghost entries in the inventory
- C-style array implementation with manual memory management
- Fixed size limit of 20 items
- Potential memory leaks from `new Item()` allocations without corresponding `delete` calls
- Inefficient item removal process

### Investigation & Analysis

Upon examining the `remove_item()` function, we found that it only decremented item quantities but never actually removed items from the underlying data structure. The inventory used a C-style array (`Item *items[20]`) with manual memory management, which led to several problems:

1. **Memory Management Issues**: Manual `new` allocations without proper cleanup
2. **Fixed Size Limitation**: Hard-coded 20-item maximum capacity
3. **Inefficient Operations**: No built-in methods for dynamic resizing or element removal
4. **Type Safety**: Using `int` for array indices instead of `size_t`

### Solution Implemented

We implemented a comprehensive fix that addressed both the core bug and underlying code quality issues:

#### Core Bug Fix

- Modified `remove_item()` function to check if quantity reaches 0
- Added `items.erase(items.begin() + item_index)` to completely remove items
- Provided user feedback when items are completely removed

#### Data Structure Optimization

- **Replaced C-style array with `std::vector<Item>`**
  - Dynamic sizing (no more 20-item limit)
  - Automatic memory management
  - Built-in methods for efficient operations
  - Exception safety

#### Code Quality Improvements

- Added missing includes: `<vector>` and `<climits>`
- Removed manual memory management (`new`/`delete`)
- Updated loops to use `size_t` instead of `int` for type safety
- Used `emplace_back()` for efficient item creation
- Fixed const correctness in `Item::is_match()` method
- Replaced manual size tracking with `vector.size()` and `vector.empty()`

### Technical Benefits

The migration from C-style arrays to `std::vector` provided several advantages:

- **Memory Safety**: Automatic cleanup prevents memory leaks
- **Dynamic Scaling**: Inventory can grow beyond 20 items as needed
- **Performance**: Efficient insertion and removal operations
- **Code Clarity**: Cleaner, more readable implementation
- **Standard Library Integration**: Better compatibility with modern C++ practices

### Result

The inventory system now properly removes items when their quantity reaches zero, eliminating ghost entries.
