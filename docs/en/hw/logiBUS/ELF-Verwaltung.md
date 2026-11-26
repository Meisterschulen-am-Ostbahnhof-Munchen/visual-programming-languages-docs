# ELF manager (graphical interface)

The ELF manager (`scripts_central/elf_manager_gui.py`) is a small graphical tool for installing single ELF libraries on a logiBUS node without repeating the complete preload. It uses only the Python standard library (tkinter). Background on the ELFs is on [Loading missing ELFs onto the trainer board](ELFs-auf-das-Board-laden.md), background on the scripts on [Deploy scripts and launches](Deploy-Skripte-und-Launches.md).

> **Note:** This page describes the program as read from its source. It has not been tested on hardware.

## Starting

- From the 4diac IDE via External Tools or the launch `RunSkript_ElfManager_AX` (set as favorite).
- Or in `scripts_central` with `python elf_manager_gui.py [host]`. The default host is `logibus.local`.
- According to the developers, the TrainingsInstaller creates a shortcut "logiBUS ELF-Verwaltung" from the first release after the merge (not verified).

## Procedure

1. **Connect:** Enter the host and press "Verbinden / Aktualisieren". The program resolves the host, checks that it is on the internal network and reachable, and reads architecture and `FORTE_ABI` of the node. If the architecture does not fit (firmware too old or too new) it stops with a message. According to the developers `FORTE_ABI` 7 applies, i.e. firmware from b-199. `isobus_fs` and ELFs on the ESP32-S31 exist only from b-214 (developer information, not verified).
2. **List:** All ELF libraries of the repo appear with version, state on the node and the column "Wird geladen". It shows "ja" if the library is in the active manifest. The active one is the alphabetically first `*.libs.json`, because that is the one the loader takes.
3. **Select:** A click (or the space bar) checks (☑) or unchecks (☐) a library.
   - "Nur Grundausstattung" checks `PRELOAD_LIBS` with their dependencies.
   - "Aktuelles Manifest" checks what is currently loaded.
4. **Install:** "Angehakte installieren". After a confirmation, the checked libraries and their `requires` (from `MANIFEST.MF`) are resolved, at most 64. Then the same procedure as the preload runs: upload ELFs, delete other manifests and all `*.fboot` on the node, write `elf_grundausstattung.libs.json`.
5. **Restart:** The change takes effect only after the node restarts. The "Weboberfläche" button opens the node's page in the browser. The log window at the bottom shows all output.

## Fill level bars

Two bars at the top, "Speicher (/data)" and "RAM (PSRAM)", show the load of the node. The source is `GET /space/?json` (according to the firmware developers with the fields `total`, `used`, `psram_size`, `psram_free`, not verified). Older firmware only delivers the HTML page `/space/` (from b-214); the program then reads the PSRAM value from `/deviceinfo/`. If values are missing, it shows "keine Angabe (Firmware zu alt?)". The bars are refreshed only when connecting and after an installation; according to the developers the query takes about 1 s. The RAM bar also counts FORTE and buffers, not only the ELFs.

## Size and sorting

The list has the additional columns "Größe" (in kB, the ELF in the repo for the architecture of the node) and "% /data" (share of this ELF in the total memory of `/data`). The percentage appears only if the node has reported the size of `/data`. A click on a column header sorts the list, a second click reverses the order (▲ ascending, ▼ descending). The summary line at the bottom shows the size of the selection including dependencies, for example "24 angehakt (max. 64), 5711 kB = 71 % von /data" (example from the developers' description).

## Status in the column "Auf dem Knoten"

| Status | Meaning |
|---|---|
| aktuell | SHA256 of the ELF on the node equals the one in the repo |
| anderer Stand | same file name, different hash |
| alte Version | another version number of the library is on the node |
| fehlt | none of it on the node |
| keine ELF im Repo | no ELF exists for this architecture |

"fehlt", "alte Version" and "anderer Stand" are shown in red. Libraries for CAN2 carry the suffix "(CAN2, nicht am Trainer)".

## Common case: UNSUPPORTED_TYPE on deploy

If the IDE reports `UNSUPPORTED_TYPE` on deploy, the library is usually not in the manifest of the node. The IDE does not load ELFs. Remedy: check the library in the ELF manager, install, restart the node. According to the developers, exercise 156_AX additionally needs `convert` and `logiBUS_utils`.

## Typical case

The file system exercises (156/156b) need `isobus_fs`, which is not part of the base set: check `isobus_fs`, install, restart the node.

## Important

- The loader only loads libraries listed in the manifest. An ELF that only lies in `elf-libs/` does not exist for FORTE.
- Installing deletes other manifests and all boot files on the node.
