# TASK SCHEDULER

**Platform:** Windows, Linux  

This software can be used to schedule tasks, run software executables, or trigger CLI-based notifications upon time entered.

---

## How to Use

### Creating a New Task
When creating a new task, enter the following:

- **Task Title** 
- **Task Message**
- **Task Time**  
  Format: `YYYY-MM-DD HH:MM`
- **Task Type**
  - `1` → CLI-based notification
  - `2` → Run a system executable file

After entering the details, press **"ENTER"** to create the task.

---

### Viewing All Loaded Tasks
- Select **"List All"**
- All currently loaded tasks will be displayed
- To exit this screen, press **Enter**

---

### Program Exit Behavior
When exiting the program:
- The scheduler will first complete any assigned task
- The program then exits **gracefully**
