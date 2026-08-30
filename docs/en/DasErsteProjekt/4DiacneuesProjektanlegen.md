# Creating a new 4Diac project

**Basic understanding of 4Diac**
**4Diac consists of several parts (3)**

1. IDE = Programming on the PC
2. FORTE = Program on the target device (DIN rail moped)
3. Type Library = Block library (part in FORTE and part in the IDE).

**Starting or creating a new project**

1. Start the 4Diac IDE (desktop shortcut). -> A window with the workspace opens.
2. Select or create a new workspace. (Each workspace name can only be used once; if necessary, add a number 1... to the name.)

![Workspace selection dialog at startup](https://user-images.githubusercontent.com/113907476/212979811-deadc740-e1f7-4815-a421-7d4b1edd067f.png)

1. Confirm the workspace with Launch. -> The workspace opens if an existing one is selected. If a new one is created, the 4Diac start page opens.

![Confirm workspace with Launch](https://user-images.githubusercontent.com/113907476/212980748-9a46691d-f7fe-4e64-9a20-73502b833b91.png)

1. To create a new project, click the "Hide" button (highlighted in the image) in the top right corner. -> A new workspace opens.

![Button Hide to collapse start page](https://user-images.githubusercontent.com/113907476/212981529-ac822fb3-5df2-4912-8857-0f7c4c5f2cde.png)

1. To create a new project, right-click in the highlighted area in the image. -> A window opens; select "New" -> then select "4diac IDE Project..."

![Right click New 4diac IDE Project](https://user-images.githubusercontent.com/113907476/212982388-dc8191de-7e9e-4451-9762-8c94da51cd54.png)

1. Enter the project name. (The program must be named "test" if the controller is to automatically restart whenever the DIN rail module is connected.)
2. After entering the name, confirm with "Finish". -> The new project appears in the selection tree on the left under "test".

![New project test in navigation tree](https://user-images.githubusercontent.com/113907476/212984431-23b4a7f2-edf4-4399-be3b-f4079403ee7d.png)

1. Open the "test" project in the selection tree on the left. -> "test" expands. Right-click on the lower "test" entry -> a window opens. Select "New" -> another window opens. Select "Application..."

-> A window opens with "New Application".

![New Application dialog window](https://user-images.githubusercontent.com/113907476/212984600-42e91f6c-5baf-4c19-b352-ee5a0369f9e4.png)

1. Assign an application name mapping and confirm with Finish. -> Application created.

Mapping can now begin. Further instructions can be found in File > Create New Controller.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
