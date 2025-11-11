# .claude/ Directory

This directory contains **Claude Code-specific context and instructions** for working on this project.

## 📁 What's Here

| File | Purpose | Read When |
|------|---------|-----------|
| **[state.md](state.md)** | Current state & next actions | **READ THIS FIRST** ⭐ |
| **[context.md](context.md)** | Project architecture & design | Need implementation details |
| **[workflows.md](workflows.md)** | Common development tasks | Need to do specific task |
| **README.md** | This file - directory overview | Understanding structure |

## 🎯 Quick Start for Claude Instances

**If you're a Claude instance starting work on this project:**

1. **READ [state.md](state.md) FIRST** - It tells you:
   - What's the current state
   - What to do next
   - How to build/test
   - Expected results

2. **Then [context.md](context.md)** - If you need to understand:
   - Project architecture
   - Tech stack choices
   - Design decisions

3. **Then [workflows.md](workflows.md)** - If you need to:
   - Perform common tasks
   - Follow established patterns
   - Understand processes

## 🤔 Why This Directory Exists

**Problem**: Each new Claude instance starts with no knowledge of:
- What's been done
- What's the current state
- What to do next

**Solution**: Standardized `.claude/` directory with clear instructions.

Similar to:
- `.github/` - GitHub-specific configuration
- `.vscode/` - VS Code settings
- `.git/` - Git repository data

## 📝 Maintaining These Files

### state.md
- **Update**: After every major change
- **Contains**: Current status, next actions, test results
- **Most important**: Keep "IMMEDIATE NEXT ACTION" up to date

### context.md
- **Update**: When architecture changes
- **Contains**: Tech decisions, design rationale
- **Stable**: Rarely changes once established

### workflows.md
- **Update**: When adding new processes
- **Contains**: How-to guides for common tasks
- **Growing**: Adds new workflows as needed

## 🔗 Relationship to Other Docs

```
Project Documentation Structure:

/
├── README.md               ← User-facing: "What is this project?"
├── plan.md                 ← Historical: Original objectives
├── STATUS.md               ← Can be merged into README or removed
│
├── .claude/                ← Claude Code-specific ⭐
│   ├── README.md           ← You are here
│   ├── state.md            ← Current state (read first)
│   ├── context.md          ← Architecture & design
│   └── workflows.md        ← How-to guides
│
└── docs/                   ← Detailed implementation docs
    ├── sunvox_juce_v1.md
    ├── sunvox_juce_v2.md
    └── research.md
```

## 🚀 Benefits

✅ **Consistent**: Every Claude instance gets same information
✅ **Fast**: No searching through files to understand state
✅ **Actionable**: Clear "what to do next" guidance
✅ **Maintainable**: Single place to update current state
✅ **Scalable**: Easy to add new context files as needed

## 💡 Convention Proposal

This `.claude/` directory structure is a **proposed convention** for making AI coding assistants more effective. Key principles:

1. **state.md is always the entry point**
2. **Separate concerns**: state vs context vs workflows
3. **Actionable instructions**: Tell Claude what to do
4. **Expected results**: Define success criteria
5. **Keep updated**: State changes frequently, context rarely

If this works well, it could become a standard for AI-assisted development projects!

---

**For humans**: This directory is for Claude Code. You can safely ignore it, or use it to understand what instructions Claude instances receive.
