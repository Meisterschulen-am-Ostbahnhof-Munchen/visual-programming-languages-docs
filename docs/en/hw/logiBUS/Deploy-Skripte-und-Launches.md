# Deploy Scripts and Launches

This page describes how programs get from the 4diac IDE onto the logiBUS® training nodes (ESP32), and which scripts and launch configurations exist in the training project for that.

!!! info "Where is what?"
    All paths are relative to the `Ventilsteuerung/` folder of the training project.

    - Python scripts: `scripts_central/`
    - Per workspace (`test_AX`, `test_B`, `test_VV`): `scripts/` (`.bat` for Windows, `.sh` for Linux) and `Launches/` (`.launch` files for the 4diac IDE)

## Overview: two ways onto the node

| Way | What is transferred | When |
| --- | --- | --- |
| **Online deploy** from the 4diac IDE (`Deploy_App_*`) | The application is loaded directly into the running FORTE instance. | Quickly trying out an exercise. The application is gone after a restart. |
| **Boot file deploy** (Python scripts) | `.fboot`, library manifest (`.libs.json`) and the required ELF libraries are copied to the node via HTTP. | Permanent installation. FORTE loads the boot file on the next start. |

For the online deploy, the node must first be prepared with the basic set of ELF libraries (see [Preparing a node](#preparing-a-node-preload)). Otherwise FORTE reports `UNSUPPORTED_TYPE` for function blocks whose library is missing.

## Python scripts in `scripts_central/`

All scripts are plain Python (standard library only, no `pip` installation needed). The command examples on this page are to be run from the `Ventilsteuerung/` folder. The `.bat` scripts and launches set the working directory themselves.

### Deploy and libraries

| Script | Purpose |
| --- | --- |
| `make_libs_manifest.py` | Creates `boot-files/<boot file>.libs.json` locally. No network access. The option `--out <path>` writes the manifest to a different location (test run). |
| `make_4diac_training1_deploy.py` | Uploads the boot file, the manifest and the required ELF libraries to the nodes listed in `NODE_ORDER`. |
| `make_4diac_training1_deploy_dido.py` | Deploy for the DIDO tester: as above, plus VT pool (`DefaultPool.iop`), visibility table (`DefaultPool.vis.json`) and web client (`apixon-diodo.html`). Target node as argument, default `logibus.local`. |
| `make_4diac_training1_elf_preload.py` | Prepares a node for the online deploy (basic set only, no boot file). |
| `deploy_common.py` | Not a script of its own but a shared module: mapping of node address to boot file (`NODE_BASES`, `NODE_ORDER`), boot file paths and the list of the basic set (`PRELOAD_LIBS`). |
| `elf_libs_manifest_lib.py` | Logic behind the manifest: which 4diac type belongs to which library, `requires` from `MANIFEST.MF`, node architecture (`riscv32` or `xtensa`) and the firmware limits. |

### Pool generation and checks

| Script | Purpose |
| --- | --- |
| `compile_iso_designer_project.py` | Compiles an ISO Designer project from the command line (`ISODesigner.exe /Compile`). Required argument `--pool-dir`. Windows only, with ISO Designer installed. |
| `GcfScript.py` | Generates the `.gcf` constant files for 4diac from `DefaultPool.iop.h` (and optionally `DefaultPool.jop`). |
| `list_mask_objects.py` | Reads the pool's masks and writes the visibility tables (`.vis.csv`, `.vis.json`). |
| `check_mixed_numeric_pool_imports.py` | Finds `.SUB` files that import VT constants from several different pools. |

!!! warning "Do not edit generated `.gcf` files by hand"
    `GcfScript.py` rebuilds the `.gcf` files completely from `DefaultPool.iop.h` every time. Constants added by hand are lost on the next run. Make changes in ISO Designer, then run the build again.

## Sequence of a boot file deploy

`make_4diac_training1_deploy.py` works through the nodes one after another:

1. **Check files.** If a boot file (`boot-files/…fboot`) is missing, the script aborts. The boot file must have been exported from the 4diac IDE beforehand. The script builds nothing itself.
2. **Check the node.** The name is resolved once. Only nodes in the internal network are allowed (`10.x`, `172.16`–`172.31`, `192.168.x`, `169.254.x`, `*.local`). Unreachable nodes are skipped.
3. **Check the architecture.** The node's architecture must match the ELF libraries, otherwise nothing is uploaded for this node.
4. **Upload the boot file** (`POST /upload/<file>`). If the node has the new firmware, the file is compared by SHA-256 hash. Unchanged files are skipped, uploaded files are verified afterwards.
5. **Remove old boot files** that belong to this node.
6. **Manifest and ELF libraries.** The script determines the required libraries including `requires` from the boot file, cleans up old versions in `elf-libs/` and uploads missing ELF files to `elf-libs/`.
7. **Upload the manifest last.** If at least one ELF upload failed, the manifest is deliberately not uploaded.

Firmware limits: at most 64 libraries per node and at most 8 `requires` per library. If a limit is exceeded, the script prints a warning.

!!! warning "The script does not restart the node"
    New files only become active after a restart, for example with the Reboot button on `http://<ip>/`. If the summary reports an error for a node, do **not** restart it. Repeat the deploy instead.

!!! note "For the training network only"
    The scripts transfer unencrypted over HTTP and without login. This is intended for the isolated training network. Productive IoT/OT systems need transport encryption (HTTPS/TLS) and access control.

!!! warning "There is no dry run"
    The script really uploads to the node. Before repeated test runs, check the free memory at `http://<ip>/space/`. An almost full file system can be corrupted by further uploads and is reformatted on the next start. All files are then gone.

### Preparing a node (preload)

`make_4diac_training1_elf_preload.py` copies the basic set (`PRELOAD_LIBS` in `deploy_common.py`, plus their `requires`) to `/data/elf-libs/` and creates a manifest of its own without a boot file. All other manifests and all `.fboot` files on the node are **deleted**: FORTE then starts empty but with the libraries loaded, and the exercise arrives via online deploy from the IDE.

    python scripts_central/make_4diac_training1_elf_preload.py                                 # logibus.local
    python scripts_central/make_4diac_training1_elf_preload.py 192.168.178.45   # specific node

`Funk`, `DataPanel`, `BlinkMarine` and `logiBUS_bosch` are not part of the basic set. The "Trainer" board has no CAN2. Here too, new files only become active after a restart of the node.

A later normal deploy replaces the preload manifest with its own. The ELF files of the basic set stay in place and are skipped by hash.

The node addresses are kept in `deploy_common.py` and `elf_libs_manifest_lib.py`. If a node is replaced, they must be adjusted there.

## Launch configurations in the 4diac IDE

The files in `Launches/` appear in the IDE under *Run As* or *Run Configurations*. There are three kinds:

| Kind | File name | What it does |
| --- | --- | --- |
| **External tool** | `RunSkript_<Name>.bat.launch` | Starts the script of the same name from `scripts/`. The working directory is the workspace's `scripts/` folder. |
| **4diac deployment** | `Deploy_App_<Name>.launch` | Online deploy of the system entry (`.sys`) to the devices and resources selected in the launch. |
| **Launch group** | `Launch_Deploy_App_<Name>.launch` | Runs several launches one after another. |

### Workspace `test_AX`

| Launch / script | Content |
| --- | --- |
| `RunSkript_DeployAX.bat.launch` | `RunSkript_DeployAX.bat`: first `make_libs_manifest.py`, then `make_4diac_training1_deploy.py` (boot file deploy). |
| `RunSkript_MakeLibsManifestAX.bat.launch` | Only create the manifest (local). |
| `RunSkript_PreloadELF_AX.bat.launch` | Prepare the node (preload, see above). |
| `RunSkript_CheckMixedPoolImports_AX.bat.launch` | Check for mixed pool imports. For Linux there is `RunSkript_CheckMixedPoolImports_AX.sh`. |
| `RunSkript_Build<Pool>_AX.bat.launch` | Build a pool: compile the ISO Designer project, delete old `.gcf` files, run `GcfScript.py` and `list_mask_objects.py`. |
| `RunSkript_ALL_AX.bat.launch` | Runs all build scripts one after another. The chain stops at the first error. |
| `Deploy_App_AX.launch` | Online deploy of `test_AX.sys` to `FORTE_PC_AX` and `EMB_RES_AX`. |
| `Launch_Deploy_App_AX.launch` | Group: first `RunSkript_BuildAX.bat` (waits for it to finish), then `Deploy_App_AX`. |
| `RunSkript_Deploy_DIDO_AX.bat` (no launch) | `make_4diac_training1_deploy_dido.py`. Arguments are passed through, for example an address instead of `logibus.local`. |

Build scripts exist for these pools: `BuildAX` (standard pool), `BuildEmpty`, `BuildPWM`, `BuildPWM12`, `BuildTECU`, `BuildHorse`, `BuildDIDO`, `BuildJoystick`, `BuildTC_SC`, `BuildScroll`, `BuildPI`, `BuildAI`, `BuildAI_Calibrate_2P`, `BuildAI_Calibrate_3P`, `BuildDreieck`, `BuildHystereseHorizontal`, `BuildHystereseVertikal`.

### Workspaces `test_B` and `test_VV`

- `test_B`: The scripts are called `RunSkript_Workspace_<Pool>_B.bat` (and `.sh`). `RunSkript_ALL_B.bat` builds all pools. `Launch_Deploy_App_B` first runs `RunSkript_ALL_B.bat` and then `Deploy_App_B` (target `FORTE_PC_B`).
- `test_VV`: One script, `RunSkript_Workspace_VV.bat`. The `Deploy_App_*` launches belong to the OPC UA examples (`CLIENT_SERVER`, `OPC_UA_RES`, `OPC_UA_SUB`, `PUBLISH_SUBSCRIBE` and variants) and deploy to several devices (for example `FORTE_PC_A` and `FORTE_PC_B`). The matching `Launch_Deploy_App_*` groups contain only the deploy.

!!! note "Linux"
    The `.sh` variants only run `GcfScript.py`. Compiling the ISO Designer project needs Windows because `compile_iso_designer_project.py` calls `ISODesigner.exe`. The installation path is fixed in the script (ISO Designer 5.7.2).

## Typical workflows

**Quickly test a new exercise (online deploy)**

1. Once: run `RunSkript_PreloadELF_AX` and restart the node. **Caution:** This deletes all `.fboot` files and manifests on the node. A permanently installed exercise is gone afterwards.
2. Run `Deploy_App_AX` in the IDE.

**Install an exercise permanently**

1. Export the boot file from the 4diac IDE.
2. Run `RunSkript_DeployAX`.
3. Only if the deploy finishes without errors: restart the node (Reboot button on `http://<ip>/`). If it reports an error, repeat the deploy and restart only afterwards.

**Pool changed in ISO Designer**

1. Run the matching `RunSkript_Build…` (or `RunSkript_ALL_AX`).
2. Then refresh the 4diac IDE and deploy again.
