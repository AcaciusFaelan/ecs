# Project Context: some_game

## Gemini Instructions & Rules
1.  **Context Management:**
    - When the user says "write the context of this chat into the context file" (or similar), summarize the current session and write it into this file (`gemini.md`).
    - On starting a new session, read this file to regain project-specific context.
    - **Meta-Rule:** When the user defines a new rule or action, automatically add it to this file (`gemini.md`).

2.  **No Code Generation/Modification:**
    - **Strict Rule:** Do NOT generate or modify code files unless explicitly instructed to do so.
    - This is a learning project.

3.  **Explanation Style:**
    - Focus on explaining concepts using the following structure:
        - **Concept Definition:** Precise, unambiguous definitions.
        - **Core Principles:** Underlying mechanisms and logic.
        - **Use Cases:** Practical applications and scenarios.
        - **Key Parameters:** Important variables and their impact.
        - **Limitations:** Constraints and potential pitfalls.
        - **Comparative Analysis:** Contrasting with related concepts.
        - **Best Practices:** Recommended approaches for effective use.

4.  **Defined Actions:**
    - **Generate Git Commit:**
        - **Trigger:** "Commit the current changes" (or similar).
        - **Scope:** Identify files/modules to include.
        - **Type:** Categorize (feat, fix, chore, refactor, etc.).
        - **Subject:** Imperative mood, <50 chars.
        - **Body:** Detailed explanation (optional, <72 chars/line).
        - **Footer:** Reference issues/breaking changes.
    - **End of Session:**
        - **Trigger:** "End of session" (or similar).
        - **Scope:** Current session history.
        - **Action:** Write session context to `gemini.md`.
        - **Commit:** Make appropriate git commit with defined action.

## Session Summary (Jan 6, 2026)
- Initial setup of the project context file.
- Established that this file is the primary project memory.
- User defined strict rules against code generation/modification to focus on learning.
- User defined specific criteria for conceptual explanations.
- User defined specific criteria for Git commit generation.
- User defined "End of session" action to automate context saving and committing.

## Session Summary (Jan 12, 2026)
- Discussed and designed a custom ECS architecture using Sparse Sets for component storage.
- Defined `Entity` type and `NULL_ENTITY` in `src/ecs/definitions.hpp`.
- Implemented `SparseSet<T>` template in `src/ecs/sparse_set.hpp`, focusing on O(1) lookups and contiguous memory iteration.
- Implemented the "Swap and Pop" removal strategy to maintain dense array packing.
- Designed a `View` system in `src/ecs/view.hpp` using C++23 variadic templates to iterate over entities with multiple components.
- Discussed "Driver" sets in Views to optimize iteration performance.
- Clarified C++ template patterns, header-only implementation requirements, and vector memory management.
- Fixed a logic bug in `SparseSet::add` where the dense index was calculated before insertion.

## Session Summary (Jan 13, 2026)
- Reviewed pseudocode in `notes.txt` for `SparseSet::remove` logic ("Swap and Pop").
- Identified a missing step in the initial pseudocode: updating the `sparse` index for the moved/swapped entity.
- Verified the corrected pseudocode which included `sparse[swappedEntity] = holeIndex`.
- Validated the actual implementation in `src/ecs/sparse_set.hpp`, confirming it correctly implements the optimized "overwrite and pop" strategy.
- Recommended adding an existence check (`sparse[entity] == NULL_ENTITY`) at the start of `remove` to prevent segfaults on invalid entity removal.
