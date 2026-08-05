# Read-Only Settings (`settingsReadOnly.ini`)
## Introduction
In logiBUS® systems, configuration values and parameters are managed in INI files on the ECU's file system. In addition to the freely writable standard configuration file (`settings.ini`), the system supports a read-only settings file: **`settingsReadOnly.ini`**.
This feature is used to permanently freeze factory settings, manufacturer-defined system parameters, fixed communication addresses, or critical hardware and security options. This prevents important parameters from being accidentally changed by operators or by the control system itself.
---
## Concept of the Two Configuration Files

The ECU distinguishes between two levels of configuration storage:

| File | Purpose | Writable? | Typical Contents |

|---|---|---|---|

| **`settingsReadOnly.ini`** | Factory Settings & System Defaults | ❌ No (Write-protected) | ISOBUS source addresses (Node SAs), hardware pin assignments, fixed boot times |

| **`settings.ini`** | User & Runtime Settings | ✅ Yes (Read & Write) | User preferences, dynamic operating parameters, selectable limit scaling |

### Functionality & Startup Priority

1. **Factory Settings Priority**: During boot, the control unit first reads the file `settingsReadOnly.ini`. All sections (`[Section]`) and keys (`KEY`) defined within it are loaded in read-only mode.

2. **Automatic Purge:** If a key is located in both `settingsReadOnly.ini` and the writable `settings.ini`, the duplicate key is automatically **removed** from `settings.ini` at system startup. This ensures that no conflicting values exist and the user file remains uncluttered.

3. **Additional Loading:** All parameters that are *not* located in `settingsReadOnly.ini` are loaded from `settings.ini` and behave normally as writable files.

---

## Operational Behavior (Read & Write)

### Read Accesses (`GET`)
Parameters are read transparently. If a key is stored in `settingsReadOnly.ini`, its immutable value is always returned.

### Write Accesses (`SET`)
If an attempt is made to change a read-only key (whether via control functions or 4diac IEC 61499 function blocks), the following occurs:

* The **write attempt is rejected**.
* The value defined in `settingsReadOnly.ini` **remains unchanged**.
* The rejection of the write operation is logged and reported back to the calling block logic.

---

## Behavior in 4diac FORTE (IEC 61499 INI Blocks)

For users of 4diac FORTE control programs, the INI function blocks (`INI`, `INI_AX`, `INI_AUI`, `INI_AR`, etc.) behave as follows with read-only parameters:

* **Read event (`GET`)**: Signals the confirmation event `GETO` as usual. The protected value is present at output `VALUEO`, and `STATUS` reports `"OK"`.
* **Read event (`GET`)**: Signals the confirmation event `GETO` as usual. The protected value is present at output `VALUEO`, and `STATUS` reports `"OK"`. * **Write Event (`SET`)**:
* The **normal success event (`SETO`)** is not triggered, but rather the error event **`SETOE`** (*Set Output Error*).
* The data output **`STATUS`** provides the understandable message: **`"Key is read-only"`**.
* The output **`QO`** indicates the error state.

!!! Note "Note for Application Developers"

By evaluating the output event `SETOE` or the status string `"Key is read-only"`, the 4diac application can react specifically to read-only parameters (e.g., displaying a note on the visualization).

---

## Importing and Managing Factory Settings

The file `settingsReadOnly.ini` is located on the ECU's memory under:

/data/settingsReadOnly.ini`

### Transferring to the ECU
Importing or updating the factory settings is easily done via the ECU's integrated **Web Interface** (File Server):

1. Connect to the ECU's web interface using a web browser.

2. Navigate to the file management (`/data`).

3. Upload your prepared `settingsReadOnly.ini` file.

4. After restarting the ECU, the read-only parameters will take effect.

## Behavior if File Is Missing
If `settingsReadOnly.ini` is not present on the ECU, the system will start normally without any limitations. All keys in `settings.ini` remain fully writable, as before.

---

## Practical Example

### Example file `settingsReadOnly.ini` (factory settings):

```ini
[CF-A]
NODE1_SA = 128
bootTimeVT = 90

[System]
DeviceName = LOGIBUS-NODE-01

### Example file `settings.ini` (user settings):

```ini
[CF-A]
UserLanguage = DE

[User]
OperatorID = 42
**Result in operation:**

* `NODE1_SA` (`128`), `bootTimeVT` (`90`), and `DeviceName` (`"LOGIBUS-NODE-01"`) are protected and cannot be modified.
* `UserLanguage` (`"DE"`) and `OperatorID` (`42`) can be freely modified and permanently saved by the controller.
* If an old value, `NODE1_SA = 130`, was accidentally present in `settings.ini`, the control unit will automatically delete it during boot, ensuring that the default value, `128`, is always used.

---

## Summary & Best Practices

| Goal | Recommended Procedure |

|---|---|

| **Save Factory Settings** | Create all immutable parameters (e.g., bus addresses, security limits) in `settingsReadOnly.ini` and upload them to the control unit. |

| **Allow User Settings** | Keep parameters that the operator is allowed to adjust (e.g., language, operating modes, counter readings) exclusively in `settings.ini`. |

| **Enable Parameters** | To make a parameter writable again, remove the corresponding key from `settingsReadOnly.ini` and restart the control unit. |

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
