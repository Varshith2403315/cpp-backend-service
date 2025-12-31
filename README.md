# CPP-Background Service 
#### (currently at stage 1 and at stage 3 can be developed into Systems-heavy prohject or used in realtime apps backend)

## Overview
This project is a minimal backend service built in C++ to explore how real backend systems are designed from first principles. Instead of relying on frameworks, the codebase explicitly implements request handling, routing, and business logic to make system behavior transparent and easy to reason about.

At its core, the service provides a key–value store that evolves from an in-memory structure into a crash-safe persistent system. State is written to disk using atomic file replacement to ensure that data remains consistent across process restarts, even in the presence of failures.

The backend also enforces correctness under concurrent access by serializing operations on shared state. This prioritizes predictable behavior and safety over raw throughput, reflecting a deliberate trade-off common in early-stage or correctness-critical systems.

This project is intentionally focused on correctness, lifecycle guarantees, and explicit design decisions rather than production-scale performance or feature completeness. It serves as a foundation that can be extended into more specialized systems or real-world applications over time.

## Architecture

The backend is organized into clearly separated layers, each with a single, well-defined responsibility. This separation keeps the system easy to reason about, extend, and debug.

### Request flow
```
┌──────────┐
│ Server   │
└────┬─────┘
     │ parses request
     ▼
┌──────────┐
│ Router   │
└────┬─────┘
     │ dispatches by method + path
     ▼
┌──────────┐
│ Handler  │
└────┬─────┘
     │ executes business logic
     ▼
┌──────────┐
│ KVStore  │
└──────────┘

```

### Components

- **Server**
  - Entry point for all requests
  - Parses raw request input
  - Performs basic validation
  - Delegates routing decisions
  - Does **not** contain business logic
  - Does **not** own application state

- **Router**
  - Performs coarse-grained dispatch based on HTTP method and path
  - Distinguishes between:
    - missing routes (`404 Not Found`)
    - unsupported methods (`405 Method Not Allowed`)
  - Maps requests to handlers
  - Stateless and framework-independent

- **Handlers**
  - Implement request-specific business logic
  - Interpret the semantic meaning of requests
  - Invoke storage operations through defined interfaces
  - Translate domain results into HTTP responses
  - Stateless by design

- **KVStore**
  - Owns all application state
  - Manages:
    - in-memory data
    - persistence to disk
    - concurrency control
  - Loads state at startup
  - Persists changes on mutation
  - Guarantees thread-safe access

### Design principles

- Single responsibility per layer
- Clear ownership of state and synchronization
- No cross-layer leakage of concerns
- Predictable behavior as the system evolves

## Persistence Design

The KVStore is designed to be durable across process restarts while keeping the persistence logic simple and explicit.

- State is persisted as a snapshot to a file on disk.
- On startup, the store loads the persisted file (if present) and reconstructs the in-memory state.
- Persistence is triggered only on state mutation (`put`, `erase`), not on reads.

### Crash-safety strategy

- Updates are written to a temporary file first.
- After the write completes successfully, the temporary file is atomically renamed to the main data file.
- This ensures that after a crash, the system observes either:
  - the previous valid state, or
  - the new fully written state,
  but never a partially written file.

This approach prioritizes correctness and simplicity over write performance.

---

## Concurrency Model

The backend supports concurrent request handling with explicit synchronization at the storage layer.

- All access to shared state is serialized using a single coarse-grained mutex inside `KVStore`.
- The mutex protects:
  - in-memory data
  - persistence operations
- Public operations (`put`, `get`, `erase`) acquire the lock at entry and release it on exit.

### Design trade-off

- This model sacrifices throughput in favor of:
  - deterministic behavior
  - simple reasoning
  - strong correctness guarantees

Finer-grained locking or lock-free designs are intentionally deferred to future iterations.

---

## Correctness Guarantees

The system provides the following guarantees:

- **State consistency**  
  All operations observe a consistent view of the key–value store.

- **Crash safety**  
  Disk state always reflects the last fully committed snapshot.

- **Thread safety**  
  Concurrent reads and writes do not cause data races or undefined behavior.

- **Deterministic behavior**  
  Operations are serialized, ensuring predictable outcomes under concurrency.

These guarantees are enforced explicitly rather than relying on framework behavior.

---

## Limitations

This project intentionally avoids solving problems outside its current scope.

- Single-process design
- Coarse-grained locking limits parallel throughput
- Snapshot-based persistence is inefficient for large datasets
- No networked I/O (requests are simulated locally)
- No authentication or authorization
- No schema validation or advanced HTTP features

These limitations are accepted to keep the system focused and easy to reason about.

---

## Roadmap

Planned future improvements include:

- Write-ahead logging (WAL) to reduce persistence overhead
- Finer-grained or reader–writer locking
- TCP-based networking and multi-client support
- Structured data formats (e.g. JSON payloads)
- Background persistence and batching
- Metrics and basic benchmarking

Each addition will be evaluated against its impact on correctness and system complexity.

---

## How to Run

1. Build the project using a C++ compiler that supports C++17 or later.
2. Run the executable.
3. The program simulates HTTP-style requests via `main.cpp`.

Example requests:
```
POST /kv name Alice
GET /kv/name
DELETE /kv/name
GET /kv/name
```

The persisted data file is created automatically if it does not exist.
