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
- Quick commands to get started
- What to do vs what not to do

### Priority 2: This Directory (Referenced)
Consult these files when you need details:

1. **[plan.md](plan.md)** - For comprehensive project plan:
   - Objectives (complete + future)
   - Current status and limitations
   - Test validation checklists
   - Known issues

2. **[architecture.md](architecture.md)** - For architecture understanding:
   - System design and components
   - Tech stack rationale
   - Design decisions and tradeoffs
   - Key patterns and conventions

3. **[workflows.md](workflows.md)** - For specific tasks:
   - Build and test procedures
   - Debug workflows
   - Common maintenance tasks
   - Git and release operations

## 🤔 Why This Directory Exists

**Problem**: Each new Claude instance starts with no knowledge of:
- What's been done
- What's the current state
- What to do next
- How things work

**Solution**: Standardized `.claude/` directory with clear instructions.

Similar to established conventions:
- `.github/` - GitHub-specific configuration
- `.vscode/` - VS Code settings
- `.git/` - Git repository data
- `node_modules/` - Package dependencies

## 📝 Maintaining These Files

### plan.md
- **Update**: After every major change or milestone
- **Contains**: Objectives, status, limitations, test results, roadmap
- **Most important**: Keep "IMMEDIATE NEXT ACTION" section current
- **Frequency**: Changes often (weekly/daily during active development)

### architecture.md
- **Update**: When architecture changes
- **Contains**: Tech stack, system design, components, design decisions
- **Most important**: Keep design rationale documented
- **Frequency**: Changes rarely (once established, only on refactors)

### workflows.md
- **Update**: When adding new processes or tools
- **Contains**: How-to guides for common development tasks
- **Most important**: Keep commands accurate and tested
- **Frequency**: Growing (add new workflows as discovered)

## 🔗 Recommended Project Structure

```
/
├── claude.md               ← Auto-loaded entry point ⭐
│
├── .claude/                ← Claude Code-specific
│   ├── README.md           ← You are here
│   ├── plan.md             ← Project plan & objectives
│   ├── architecture.md     ← Architecture & design decisions
│   └── workflows.md        ← How-to guides for common tasks
│
└── [your project files]    ← Implementation, tests, etc.
```

**Note**: Additional project-specific docs can live in root or `/docs/` as needed.

## 🚀 Benefits

✅ **Consistent**: Every Claude instance gets same information
✅ **Fast**: No searching through files to understand state
✅ **Actionable**: Clear "what to do next" guidance
✅ **Maintainable**: Single place to update current state
✅ **Scalable**: Easy to add new context files as needed
✅ **Portable**: Drop this structure into any project

## 💡 Convention Principles

This `.claude/` directory structure is a **proposed convention** for making AI coding assistants more effective. Key principles:

1. **claude.md auto-loads**: Concise entry point with immediate action
2. **plan.md for objectives**: What's done, what's next, current state
3. **architecture.md for design**: How it works, why decisions were made
4. **workflows.md for tasks**: Step-by-step procedures for common operations
5. **Separate concerns**: Don't mix "what" with "how" with "why"
6. **Actionable instructions**: Tell Claude exactly what to do
7. **Expected results**: Define success criteria clearly
8. **Keep updated**: Plan changes frequently, architecture rarely

## 📋 Getting Started Template

When setting up `.claude/` for a new project:

1. **Copy this directory** into your project root
2. **Create `claude.md`** in root with immediate next action
3. **Fill out `plan.md`**:
   - Project goals and objectives
   - Current status
   - What's complete, what's pending
   - Test procedures
4. **Fill out `architecture.md`**:
   - Tech stack
   - System components
   - Design decisions
5. **Fill out `workflows.md`**:
   - Build commands
   - Test commands
   - Common tasks

## 🎓 Best Practices

### For claude.md (Auto-loaded)
- ✅ Keep it SHORT (under 150 lines)
- ✅ Lead with immediate next action
- ✅ Link to `.claude/` files for details
- ✅ Include quick reference commands
- ❌ Don't duplicate content from other files

### For plan.md
- ✅ Update after every milestone
- ✅ Keep objectives clear and measurable
- ✅ Document known limitations
- ✅ Maintain test validation checklists
- ❌ Don't include architecture details (use architecture.md)

### For architecture.md
- ✅ Document the "why" not just the "what"
- ✅ Include diagrams when helpful
- ✅ Explain tradeoffs in design decisions
- ❌ Don't include changing status info (use plan.md)

### For workflows.md
- ✅ Test all commands before documenting
- ✅ Include expected output
- ✅ Document troubleshooting steps
- ❌ Don't include design rationale (use architecture.md)

---

## 📖 For Humans

**This directory is for Claude Code.** You can safely ignore it, or use it to understand what instructions Claude instances receive.

If you're working alongside Claude, keeping these files updated will make every Claude session more productive.

---

**This is a proposed convention.** If it works well for you, consider sharing it or contributing to making it a standard for AI-assisted development!
