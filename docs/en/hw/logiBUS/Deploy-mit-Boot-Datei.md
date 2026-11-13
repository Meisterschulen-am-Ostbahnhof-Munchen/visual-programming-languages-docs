# Deploy with a boot file: .fboot, manifest, upload

This guide shows the way **boot file → manifest → upload** using the trainer board (workspace `test_AX`) as an example. It is the alternative to the online deploy in [Loading missing ELFs onto the trainer board](ELFs-auf-das-Board-laden.md). Background on the scripts is on the page [Deploy scripts and launches](Deploy-Skripte-und-Launches.md).

## Online deploy or boot file?

| | Online deploy | Boot file deploy |
| --- | --- | --- |
| What goes onto the board | The application is loaded into the running FORTE instance. The ELFs of the **basic set** must already be on the board via preload. | The `.fboot`, a manifest and **exactly the ELFs the `.fboot` needs**, including libraries outside the basic set such as `utils`. |
| After a restart | The application is gone. | FORTE loads the `.fboot` at startup. The board also starts with the application without the IDE. |
| Typical for | Quickly trying things out, exercises. | Permanent installation, operation without the IDE. |
| Nodes | Any reachable board (`logibus-<MAC>.local`, also `logibus.local` if only one device is on the network, or IP). | Only nodes entered in `deploy_common.py` (see below). |

## Procedure

### Step 1: Create the boot file in the IDE

In the 4diac IDE, the function **Create Forte BootFile** (also called **Create boot-files**) creates the `.fboot` of the device. One file `<System>_<Device>.fboot` is created per device, for the trainer board `test_AX_FORTE_PC_AX.fboot`. It belongs in `Ventilsteuerung/boot-files/`.

**Click path in the 4diac IDE 3.4:** Right-click the **resource** or the **device** and choose **Create Forte BootFile**. If the system has several devices, trigger the function on the first device and select the other devices in the dialog.

!!! warning "Device profile OPC UA"
    If the device's profile is set to OPC UA, **Create Forte BootFile** fails. Workaround: temporarily switch the profile to HOLOBLOC (see `OPCUA_Bootfile_Workaround.md` in the training project). The device `test_AX/FORTE_PC_AX` already has the profile HOLOBLOC and is not affected.

If you change a `.SUB` later, it only takes effect after a **new export** and a restart of the board.

### Step 2: Create the manifest

`make_libs_manifest.py` reads the types from the `.fboot`, determines the required libraries including `requires` from the `MANIFEST.MF`, and writes `boot-files/<boot file>.libs.json`. The manifest contains SHA-256 and size of the `.fboot` and the required ELFs. The script works locally only, without network access.

In the IDE: **Run → External Tools → `RunSkript_MakeLibsManifestAX.bat`**. Or on the command line in the folder `Ventilsteuerung/`:

    python scripts_central/make_libs_manifest.py

`--out <path>` changes the output file. There is no node selection here.

!!! warning "Never deploy a `.fboot` without a freshly created manifest"
    If SHA-256 or size of the boot file do not match the manifest, the device reports `WRONG`. After every new export, create the manifest again first. This also applies before checking in to the repository.

### Step 3: Upload

`make_4diac_training1_deploy.py` uploads the `.fboot`, the manifest and exactly the required ELFs to the board via HTTP (`POST /upload/<file>`), compares them by hash and does **not** restart the board. The call `RunSkript_DeployAX.bat` first runs the manifest script and then the deploy script. The exact procedure of the script is described in the section [Sequence of a boot file deploy](Deploy-Skripte-und-Launches.md#sequence-of-a-boot-file-deploy).

In the IDE: **Run → External Tools → `RunSkript_DeployAX.bat`**.

The script looks for the boot file in this order:

1. the newest stamped file `test_AX_FORTE_PC_AX_*.fboot` in `Ventilsteuerung/`,
2. `Ventilsteuerung/test_AX_FORTE_PC_AX.fboot`,
3. `Ventilsteuerung/boot-files/test_AX_FORTE_PC_AX.fboot`.

If the file is missing, it aborts with "Fehlende Dateien zuerst neu bauen/exportieren (4diac-IDE-Export)" (missing files, rebuild/export first).

### Step 4: Restart the board

FORTE only reads the `.fboot` at startup. Restart the board by hand, for example with the **Reboot** button of the web interface `http://<ip>/`.

## Which nodes does the script know?

The deploy script does not evaluate arguments. The nodes are fixed in `scripts_central/deploy_common.py`: `NODE_BASES` assigns its files to each node address, `NODE_ORDER` sets the order. Currently there is only the node `192.168.178.45` with `test_AX_FORTE_PC_AX.fboot` for `test_AX`. For an arbitrary trainer board under `logibus.local` this way does not work without further steps. Use the online deploy for that.

According to the code, a new node is entered like this (not tried out): a new entry in `NODE_BASES` and `REPO_PATHS` as well as in `NODE_ORDER` (both in `deploy_common.py`) and `NODE_ARCH` (in `elf_libs_manifest_lib.py`). The mapping of file names to paths in the repository is in `REPO_PATHS`, including that of the `.libs.json`.

## Further pitfalls

- **Outdated `.fboot`:** If a change has no effect, the device was not exported again after the change or the board was not restarted.
- **Constants from GCF files:** After a `.gcf` has been changed from outside, the IDE can create boot files with shifted addresses (with OPC UA even nested addresses). Workaround: **Refresh** in the IDE, then create again.
- **Further files:** Some nodes also need a VT object pool (`.iop` and `.vis.json`), which is listed in the node's entry in `NODE_BASES`.
