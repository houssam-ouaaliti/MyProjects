# Multiplayer Card Game

A real-time, UNO-style multiplayer card game for 2 to 4 players, built as a full-stack web application: a **Spring Boot** REST + WebSocket backend, a **React** single-page frontend and a **MySQL** database, all runnable with a single `docker compose` command.

Players register, create or join a lobby, play turn by turn with live game-state updates, chat during the match and compete on a global ranking.

## Features

- **Accounts**: registration and login
- **Lobby**: create a game, list open games, join an existing one (2 to 4 players)
- **Real-time gameplay** over WebSocket: turn order, play/draw actions, discard pile and hand sizes synchronised between all players
- **Card rules**: 4 colours plus wild cards, numbers `0-9`, `PASSER` (skip), `INVERSE` (reverse direction), `PLUS2`, `PLUS4` and `JOKER`, with clockwise / counter-clockwise turn direction
- **In-game chat**: one WebSocket channel per game
- **Disconnection handling**: a player who leaves is marked as disconnected and the game continues; if only one player remains connected, they win automatically
- **Ranking**: wins are recorded per player and displayed on a leaderboard page

## Tech stack

| Layer | Technologies |
|-------|--------------|
| Backend | Java 17, Spring Boot 4, Spring Web MVC, Spring Data JPA / Hibernate, Jakarta WebSocket |
| Frontend | React 19, Vite, ESLint |
| Database | MySQL 8 (schema and seed data in `backend/src/main/resources/init.sql`) |
| DevOps | Docker, Docker Compose, Jenkins pipeline (`Jenkinsfile`) |
| Testing | JUnit 5 (entity tests) |

## Architecture

```
┌────────────────┐   REST (/api/**)      ┌──────────────────────────┐        ┌─────────┐
│  React + Vite  │ ────────────────────► │  Spring Boot             │ ─────► │  MySQL  │
│  (port 5173)   │ ◄──────────────────── │  controllers → services  │  JPA   │  8      │
│                │   WebSocket           │  → repositories          │ ◄───── │         │
│                │   /ws/game, /ws/chat  │  (port 8080)             │        └─────────┘
└────────────────┘                       └──────────────────────────┘
```

- **REST** handles authentication, lobby operations, starting a game, playing and drawing cards, and the ranking.
- **WebSocket** pushes game-state changes and chat messages to every player of a game.
- The backend is layered: `controller` → `service` → `repositories` (Spring Data JPA) → `entity`, with `dto` classes shaping the API payloads.

### Main endpoints

| Method | Path | Purpose |
|--------|------|---------|
| POST | `/api/auth/register`, `/api/auth/login` | Account creation and login |
| GET | `/api/lobby` | List games |
| POST | `/api/lobby/create`, `/api/lobby/join/{gameId}` | Create or join a game |
| POST | `/api/game/{gameId}/start` | Start a game (at least 2 players) |
| GET | `/api/game/{gameId}` | Game state for a player |
| POST | `/api/game/{gameId}/play`, `/api/game/{gameId}/draw` | Play a card, draw a card |
| GET | `/api/ranking` | Leaderboard |
| WS | `/ws/game/{gameId}/{playerId}`, `/ws/chat/{gameId}/{playerId}` | Live game updates and chat |

## Getting started

### Option 1: Docker (recommended)

Requirements: Docker with Docker Compose.

```bash
docker compose up --build
```

Then open <http://localhost:5173>. The backend listens on port 8080 and MySQL is exposed on port 3307. The database is initialised automatically from `init.sql`.

### Option 2: Run locally

Requirements: JDK 17, Node.js 20+, a running MySQL 8 server.

1. Create the database and load the schema:

   ```bash
   mysql -u root -p -e "CREATE DATABASE IF NOT EXISTS jeux;"
   mysql -u root -p jeux < backend/src/main/resources/init.sql
   ```

2. Start the backend (database settings can be overridden with the `SPRING_DATASOURCE_URL`, `SPRING_DATASOURCE_USERNAME` and `SPRING_DATASOURCE_PASSWORD` environment variables):

   ```bash
   cd backend
   ./mvnw spring-boot:run
   ```

3. Start the frontend:

   ```bash
   cd frontend
   npm install
   npm run dev
   ```

4. Open <http://localhost:5173>. To test with several players on one machine, use a normal and a private browser window.

### Playing from several computers

Start the frontend with `npm run dev -- --host 0.0.0.0`, then open `http://<host-ip>:5173` from the other computers on the same network. The frontend reaches the backend on the same hostname, port 8080.

## Tests

```bash
cd backend
./mvnw test
```

## Project structure

```
jeu-cartes-multijoueurs/
├── backend/            Spring Boot application (controllers, services, entities, WebSocket endpoints)
├── frontend/           React application (pages, components, API and WebSocket services)
├── docs/               Project reports (in French)
├── docker-compose.yml  MySQL + backend + frontend
└── Jenkinsfile         CI/CD pipeline definition
```

## Skills demonstrated

Java 17 · Spring Boot · REST API design · WebSocket real-time communication · JPA / Hibernate · relational modelling (MySQL) · React · Docker and Docker Compose · CI/CD with Jenkins · JUnit · team project documentation

## Roadmap

Planned improvements:

- Hash passwords (BCrypt) and add token-based authentication
- Restrict CORS to configured origins and move database credentials to environment files
- Add unit tests for the game rules in `GameService`
- Update the Jenkins pipeline paths to match this repository layout
