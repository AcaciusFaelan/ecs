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