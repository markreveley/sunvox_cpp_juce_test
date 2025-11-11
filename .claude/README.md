# .claude/ Directory

This directory contains **detailed Claude Code context and workflows** for this project.

## 🎯 Entry Point

**Note**: Claude Code automatically loads `/claude.md` on startup. That file provides the critical "what to do now" context. This directory contains detailed reference documentation.

## 📁 What's Here

| File | Purpose | Read When |
|------|---------|-----------|
| **[plan.md](plan.md)** | Project plan, objectives & status | Need comprehensive status |
| **[architecture.md](architecture.md)** | Project architecture & design | Need implementation details |
| **[workflows.md](workflows.md)** | Common development tasks | Need to do specific task |
| **README.md** | This file - directory overview | Understanding structure |

## 🎯 Quick Start for Claude Instances

**If you're a Claude instance starting work on this project:**

### Priority 1: `/claude.md` (Auto-loaded ✨)
The root `claude.md` file is **automatically loaded** and tells you:
- What's the immediate next action
- Current project status
- Quick build/test commands
- What to do vs what not to do

### Priority 2: This Directory (Referenced)
Consult these files when you need details:

1. **[plan.md](plan.md)** - For comprehensive project plan:
   - Full test validation checklist
   - Objectives (complete + future)
   - Current status and limitations

2. **[architecture.md](architecture.md)** - For architecture understanding:
   - Component diagrams
   - Tech stack rationale
   - Design decisions

3. **[workflows.md](workflows.md)** - For specific tasks:
   - Build workflows
   - Debug procedures
   - Git operations

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

### plan.md
- **Update**: After every major change
- **Contains**: Objectives, status, limitations, test results
- **Most important**: Keep "IMMEDIATE NEXT ACTION" up to date

### architecture.md
- **Update**: When architecture changes
- **Contains**: Tech decisions, design rationale, component structure
- **Stable**: Rarely changes once established

### workflows.md
- **Update**: When adding new processes
- **Contains**: How-to guides for common tasks
- **Growing**: Adds new workflows as needed

## 🔗 Relationship to Other Docs

```
Project Documentation Structure:

/
├── claude.md               ← Auto-loaded entry point ⭐
│
├── .claude/                ← Claude Code-specific
│   ├── README.md           ← You are here
│   ├── plan.md             ← Project plan & objectives
│   ├── architecture.md     ← Architecture & design decisions
│   └── workflows.md        ← How-to guides for common tasks
│
├── sunvox_juce_v1.md       ← v1 implementation details
├── sunvox_juce_v2.md       ← v2 implementation details
└── research.md             ← SunVox integration research
```

## 🚀 Benefits

✅ **Consistent**: Every Claude instance gets same information
✅ **Fast**: No searching through files to understand state
✅ **Actionable**: Clear "what to do next" guidance
✅ **Maintainable**: Single place to update current state
✅ **Scalable**: Easy to add new context files as needed

## 💡 Convention Proposal

This `.claude/` directory structure is a **proposed convention** for making AI coding assistants more effective. Key principles:

1. **claude.md auto-loads**: Entry point with immediate action
2. **plan.md for details**: Comprehensive objectives, status, future plans
3. **Separate concerns**: plan vs architecture vs workflows
4. **Actionable instructions**: Tell Claude what to do
5. **Expected results**: Define success criteria
6. **Keep updated**: Plan changes frequently, architecture rarely

If this works well, it could become a standard for AI-assisted development projects!

---

**For humans**: This directory is for Claude Code. You can safely ignore it, or use it to understand what instructions Claude instances receive.
