# Loading missing ELFs onto the trainer board

Using exercise 256 (PWM frequency, `test_AX/Uebungen/Uebung_256_AX.SUB`) as an example, this guide shows how a program gets onto the trainer board by online deploy from the 4diac IDE, and what to do when the IDE reports `UNSUPPORTED_TYPE`. Background on the scripts is on the page [Deploy scripts and launches](Deploy-Skripte-und-Launches.md).

## What this is about

FORTE on the board only knows the basic blocks. The libraries used by the exercises (adapter, logiBUS IO, storage, OPC UA and others) are stored as ELF files in `/data/elf-libs/` on the board and are loaded at startup. If an ELF is missing, the IDE reports `UNSUPPORTED_TYPE` for the affected block during deploy.

The ELFs are part of the training project. They are located under `Ventilsteuerung/4diacIDE-workspace/.lib/<Lib>-<Version>/elf/riscv32/`. The script `RunSkript_PreloadELF_AX` loads the **basic ELF set** (the commonly used libraries including their dependencies) onto the board in one go. Which libraries belong to it is defined in `PRELOAD_LIBS` in `scripts_central/deploy_common.py`.

Exercise 256 only needs libraries from the basic set:

- `logiBUS_io`
- `adapter`, `adapter_types`, `adapter_conversion`, `adapter_events`, `adapter_iec61131-3`
- `net_adapter`
- `logiBUS_storage`
- `iec61131-3`, `iec61131-3-bool`, `events`

One run of `RunSkript_PreloadELF_AX` is therefore enough. The same applies to exercises 265 and 266.

## Prerequisites

- The training project is up to date (`git pull` or latest release). Only then do the ELFs match the blocks in the IDE.
- Python 3 is installed and `python` is in the path. No further packages are needed.
- The trainer board is connected to the PC by network cable. From firmware `v0.27-alpha-b-160-gaaaec75b` on, every board is called `logibus-<MAC>.local` (for example `logibus-e0c4f1.local`), and the name `logibus.local` belongs to only one device on the network (see [Hostname and mDNS](Deploy-Skripte-und-Launches.md#hostname-and-mdns)). With older firmware **all** boards announce themselves as `logibus.local`, and it is a matter of chance which one answers. In that case **connect only one board at a time**. With several boards on the same network, give the name or IP address of the board you want.
- `http://logibus.local/` opens the board's web interface in the browser. If not, the board is not reachable: check the cable and the network adapter.

## Step 1: Load the basic set

In the 4diac IDE: **Run → External Tools → `RunSkript_PreloadELF_AX.bat`**. Alternatively, double-click `test_AX/scripts/RunSkript_PreloadELF_AX.bat`.

The output lists each ELF with the status `OK` or `unveraendert (Hash stimmt), uebersprungen` (unchanged, hash matches, skipped). At the end it must say:

    ZUSAMMENFASSUNG (1/1 Knoten erfolgreich):
      - logibus.local: OK

!!! warning "The script deletes boot files and manifests"
    All boot files (`*.fboot`) and library manifests (`*.libs.json`) on the board are deleted. FORTE then starts empty and waits for the deploy from the IDE. More under [Preparing the node (preload)](Deploy-Skripte-und-Launches.md#preparing-a-node-preload).

If the script aborts with a warning, simply start it again. It skips ELFs that are already on the board.

## Step 2: Restart the board

Press the **Reboot** button on `http://logibus.local/`. FORTE only loads the new ELFs after the restart.

## Step 3: Deploy exercise 256

1. In `test_AX/sys/Training_AX/test_AX.sys`, select the SubApp **`Control`**.
2. Right-click → **Change Type**, choose the type `Uebungen::Uebung_256_AX` and save.
3. Start **Run As → `Deploy_App_AX`**. Alternatively, right-click `FORTE_PC_AX` in the System Explorer → Deploy.

The device `FORTE_PC_AX` talks to the board via `logibus.local:61499`. The address does not need to be changed.

## If `UNSUPPORTED_TYPE` appears

The message names the block type. Then check in this order:

1. **Board restarted?** Without a restart after step 1, the ELFs are on the board but not loaded.
2. **Training project up to date?** A new block in the IDE needs the matching, equally new ELF. Update the project and repeat steps 1 and 2.
3. **Library not in the basic set?** The namespace of the type shows the library, for example `adapter::events::…` belongs to `adapter_events`. If it is missing from `PRELOAD_LIBS` in `scripts_central/deploy_common.py`, it is not part of the basic set. Online deploy then returns `UNSUPPORTED_TYPE`. Example: `SPLIT_WORD_INTO_BOOLS` and `ASSEMBLE_BYTE_FROM_BOOLS` come from the library `utils`. It is not part of the basic set, so online deploy reports `UNSUPPORTED_TYPE` for them.
4. **Block not yet in the ELF?** A new block can already exist as a type in the IDE before its ELF has been rebuilt. Uploading does not help then: the ELF has to be rebuilt.

!!! info "`NO_SUCH_OBJECT` is only a consequence"
    If the console reports `NO_SUCH_OBJECT` for all connections of a block, the block itself was not created because its ELF is missing or outdated. The actual cause is further up in the console at `CREATE`. Look there first.

## Good to know

- **Free space:** `http://logibus.local/space/` shows the usage. An almost full file system can be damaged by further uploads and is reformatted at the next start. All files on the board are gone then. Repeat steps 1 and 2.
- **Next exercise:** The ELFs stay on the board. For further exercises, only repeat step 3 with the other type.
