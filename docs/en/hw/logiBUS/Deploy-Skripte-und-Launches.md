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

## Finding the node and setting its IP address

### Hostname and mDNS

A node announces itself via mDNS under a name ending in `.local`. The scripts use `logibus.local` as the default target when no node is given.

- Each board is called `logibus-<xxxxxx>.local`. `<xxxxxx>` are the last three bytes of the MAC address, for example `logibus-3a7f21.local`. The name is therefore unique per board.
- The same name is the DHCP hostname on all interfaces and the hostname of the OPC UA endpoint (`opc.tcp://logibus-xxxxxx.local:4840`).
- `logibus.local` remains as an additional name, but only if **one** board is on the network. If two devices announce the name, the board with the lower IP keeps it.
- To use a name of your own, enter it in `/data/settings.ini`:

        [mDNS]
        Hostname=my-board

  If the entry is empty or contains the old value `logibus`, the automatic name applies. A custom name is cleaned to the characters `A–Z`, `a–z`, `0–9` and `-`.

!!! warning "Older firmware"
    On devices with older firmware, **all** boards are called `logibus.local`. Which board answers is then random. In that case connect only one board at a time or address the node by its IP address. The DHCP hostname there is `espressif-eth-int`, `espressif-eth-spi1`, `espressif-eth-spi2` or `espressif`.

!!! note "State of the firmware"
    The unique names are a recent firmware change. It had not yet been tested on hardware when this page was written. If in doubt, use `ping logibus.local` or the router's web interface to check under which name and IP the node reports.

### Which address does the node get?

1. **DHCP** (default, `DHCP_CLIENT=1`): The node gets its address from the DHCP server on the network.
2. **Link-local:** If no DHCP server answers after two attempts, the node assigns itself an address from `169.254.x.x`. This applies only with `DHCP_CLIENT=1`. If the DHCP client keeps asking and a server appears, the node takes over its address.
3. **Static** (`DHCP_CLIENT=0`): The address is set in the INI file.

### INI files

The settings are INI files in the node's `/data/` directory:

| File | Content | Applies to |
| --- | --- | --- |
| `/data/ethernet.ini` | Ethernet: sections `[ETH_INT]` (internal Ethernet), `[ETH_SPI1]` and `[ETH_SPI2]` (SPI Ethernet chips, S3 boards with `_1ETH` or `_2ETH`) | builds with Ethernet |
| `/data/wlan.ini` | WLAN client and access point: `[general]`, `[WIFI_STA]`, `[WIFI_AP]` | S3 only |
| `/data/settings.ini` | General settings (hostname, ISOBUS address, object pool, custom values from 4diac) | all |
| `/data/settingsReadOnly.ini` | Fixed values that take precedence over `settings.ini` | all |
| `/data/functionalities.ini` | Which ISOBUS clients log in (VT, AUX, TC) | all |
| `/data/device.ini` | ISOBUS NAME of the control function | all |

These are all INI files of the firmware, there are no others. All are in the node's file system under `/data/`.

Internal Ethernet (`[ETH_INT]`) is found on the P4 (NodeISO20) and S31 (Trainer20). These two have no WLAN and therefore no access point.

**Static IP on Ethernet:**

    [ETH_INT]
    DHCP_CLIENT=0
    IP_ADDR=192.168.1.50
    NETMASK=255.255.255.0
    GATEWAY=192.168.1.1
    MAIN_DNS_SERVER=192.168.1.1

`IP_ADDR`, `NETMASK`, `GATEWAY` and the DNS servers only take effect with `DHCP_CLIENT=0`. Further keys per section: `BACKUP_DNS_SERVER`, `FALLBACK_DNS_SERVER`, `hostname` (DHCP hostname), `SNTP_SYNC`, `SNTP_SERVER_0` and `TZ`. Missing keys get their default value. The default IP of `[ETH_INT]` is `192.168.4.17`, that of `[ETH_SPI1]` is in the `192.168.5.x` network and that of `[ETH_SPI2]` in `192.168.6.x`.

**WLAN client with DHCP (S3):**

    [general]
    mode=WIFI_MODE_STA

    [WIFI_STA]
    WIFI_REMOTE_AP_SSID=MyNetwork
    WIFI_REMOTE_AP_PASSWORD=secret
    DHCP_CLIENT=1

Possible values for `mode`: `WIFI_MODE_AP` (default), `WIFI_MODE_STA`, `WIFI_MODE_APSTA` and `WIFI_MODE_NULL`.

!!! warning "By default every S3 opens an access point"
    Without a `wlan.ini`, an S3 runs as an access point with the SSID `xx`, the password `esp32_pwd`, the IP `192.168.4.1` and a DHCP server. Several S3 boards without their own `wlan.ini` therefore share the same SSID and the same IP. In class, give each node its own `wlan.ini` or switch on only one at a time.

### `ethernet.ini`: all keys

The three sections `[ETH_INT]`, `[ETH_SPI1]` and `[ETH_SPI2]` have the same keys. They only differ in their default values. The firmware only reads the keys listed here, there are no others. Entries marked "not verified" are not backed by the firmware code.

| Key | Default `ETH_INT` | Default `ETH_SPI1` | Default `ETH_SPI2` | Effect |
| --- | --- | --- | --- | --- |
| `DHCP_CLIENT` | `1` | `1` | `1` | `1`: address via DHCP, `0`: static address from this file |
| `IP_ADDR` | `192.168.4.17` | `192.168.5.17` | `192.168.6.17` | Static IP address |
| `NETMASK` | `255.255.255.0` | `255.255.255.0` | `255.255.255.0` | Netmask |
| `GATEWAY` | `192.168.4.1` | `192.168.5.1` | `192.168.6.1` | Gateway |
| `MAIN_DNS_SERVER` | `192.168.4.1` | `192.168.5.1` | `192.168.6.1` | First DNS server |
| `BACKUP_DNS_SERVER` | `0.0.0.0` | `0.0.0.0` | `0.0.0.0` | Second DNS server |
| `FALLBACK_DNS_SERVER` | `0.0.0.0` | `0.0.0.0` | `0.0.0.0` | Third DNS server |
| `hostname` | `espressif-eth-int` | `espressif-eth-spi1` | `espressif-eth-spi2` | DHCP hostname of this port, **not** the mDNS name (see below) |
| `SNTP_SYNC` | `0` | `0` | `0` | `1`: get the time via SNTP |
| `SNTP_SERVER_0` | `pool.ntp.org` | `pool.ntp.org` | `pool.ntp.org` | SNTP server |
| `TZ` | `CET-1CEST,M3.5.0,M10.5.0/3` | same | same | Time zone as POSIX TZ string |

- `IP_ADDR`, `NETMASK`, `GATEWAY`, `MAIN_DNS_SERVER` and `BACKUP_DNS_SERVER` only apply with `DHCP_CLIENT=0`. `FALLBACK_DNS_SERVER` is also set with DHCP.
- `hostname`: An empty value or the old default (`espressif-eth-int`, `espressif-eth-spi1`, `espressif-eth-spi2`) means the device name is used. The mDNS name does not depend on this key, see [Hostname and mDNS](#hostname-and-mdns).
- **SNTP and `TZ` effectively apply to the whole node, not per port.** The first port with `SNTP_SYNC=1` starts SNTP with its server and its time zone, all further ones are skipped. If SNTP was already started from `wlan.ini` (WLAN starts before Ethernet), WLAN wins. Without `SNTP_SYNC=1` somewhere, `TZ` is not set anywhere.

### `wlan.ini`: all keys

This file only exists on the S3. Here too the firmware only reads the keys listed. The `[WIFI_STA]` section applies with `mode=WIFI_MODE_STA` and `WIFI_MODE_APSTA`, the `[WIFI_AP]` section with `WIFI_MODE_AP` and `WIFI_MODE_APSTA`.

**`[general]`**

| Key | Default | Effect |
| --- | --- | --- |
| `mode` | `WIFI_MODE_AP` | `WIFI_MODE_NULL`, `WIFI_MODE_STA`, `WIFI_MODE_AP` or `WIFI_MODE_APSTA` |

**`[WIFI_STA]`** (node as WLAN client)

| Key | Default | Effect |
| --- | --- | --- |
| `WIFI_REMOTE_AP_SSID` | `WLAN-SSID` | Name of the WLAN the node connects to |
| `WIFI_REMOTE_AP_PASSWORD` | `PASSWORD` | Password of this WLAN |
| `SCAN_METHOD` | `WIFI_FAST_SCAN` | `WIFI_FAST_SCAN` or `WIFI_ALL_CHANNEL_SCAN` |
| `MAXIMUM_RETRY` | `5` | Passed to ESP-IDF (`failure_retry_cnt`). According to ESP-IDF: retries per access point when connecting before the next one is tried (not verified) |
| `CNN_MAXIMUM_RETRY` | `5` | The firmware's own limit: after every disconnect it reconnects until this number is reached. After that the firmware does **not** reconnect any more until the next restart. With an IP address the counter is reset. At startup the firmware waits until the connection is up or the attempts are used up |
| `WIFI_SCAN_AUTH_MODE_THRESHOLD` | `WIFI_AUTH_WPA2_PSK` | Weakest encryption the node accepts (text values see below) |
| `RSSIThreshold` | `-127` | Minimum signal strength in dBm. `-127` means no limit (not verified) |
| `SAE_PWE_H2E` | `WPA3_SAE_PWE_BOTH` | WPA3 SAE method (text values see below) |
| `SAE_H2E_IDENTIFIER` | empty | Passed to ESP-IDF, according to ESP-IDF the password identifier for WPA3 H2E (not verified) |
| `DHCP_CLIENT` | `1` | `1`: address via DHCP, `0`: static address from this file |
| `IP_ADDR` | `192.168.4.16` | Static IP address |
| `NETMASK` | `255.255.255.0` | Netmask |
| `GATEWAY` | `192.168.4.1` | Gateway |
| `MAIN_DNS_SERVER` | `192.168.4.1` | First DNS server |
| `BACKUP_DNS_SERVER` | `0.0.0.0` | Second DNS server |
| `FALLBACK_DNS_SERVER` | `0.0.0.0` | Third DNS server |
| `IP_DI` | `0` | Only with `DHCP_CLIENT=0`: the level of the pin `IP_DI_PIN` (0 or 1, read once at startup) is ORed into the **last octet** of the static IP. Example: `IP_ADDR=192.168.4.16`, pin high gives `192.168.4.17`. If the last octet is already odd, nothing changes. It is only one bit, so only two addresses |
| `IP_DI_PIN` | `-1` | GPIO number for `IP_DI` and `hostname_DI`. The pin is configured as an input with pull-down at startup. The firmware does not check which pins are allowed (not verified) |
| `hostname` | `espressif` | DHCP hostname in the WLAN client network. Empty or `espressif` means the device name is used |
| `hostname_DI` | `0` | `1`: appends the level (0 or 1) of the pin `IP_DI_PIN` to the DHCP hostname, for example `logibus-3a7f210` |
| `SNTP_SYNC` | `0` | `1`: start SNTP. The firmware then waits up to 10 × 2 s for the time, **before** starting WLAN. Startup is delayed by up to about 18 s |
| `SNTP_SERVER_0` | `pool.ntp.org` | SNTP server |
| `TZ` | `CET-1CEST,M3.5.0,M10.5.0/3` | Time zone as POSIX TZ string, set after SNTP synchronisation |
| `STATIC_DNS_RESOLVE_TEST` | `0` | Diagnostics: with `1`, `RESOLVE_DOMAIN` is resolved once and the result is written to the log. This happens **before** WLAN starts, so without a connection the test practically always fails |
| `RESOLVE_DOMAIN` | `www.google.com` | Domain for this test |

!!! warning "`IP_DI_PIN` must be set"
    If `IP_DI=1` or `hostname_DI=1` and `IP_DI_PIN` stays at `-1`, the firmware's behaviour is undefined. Always enter a valid pin then.

!!! warning "The log shows the WLAN password in clear text"
    When connecting, the firmware writes the SSID **and** the password to the log in clear text (`connected to ap SSID:… password:…`), also on failure. Do not pass on logs together with `wlan.ini` credentials.

**`[WIFI_AP]`** (node as access point)

| Key | Default | Effect |
| --- | --- | --- |
| `WIFI_AP_SSID` | `xx` | Name of the access point. For exactly `xx` (the default) the firmware sets the first two bytes of the SSID to `0xFF`: the SSID then consists of two non-printable bytes and is not `xx`. How it is displayed on a phone or PC is not verified |
| `WIFI_AP_PASSWORD` | `esp32_pwd` | Password. If it is empty, an **open network** is forced (`WIFI_AUTH_OPEN`) |
| `WIFI_AP_CHANNEL` | `1` | WLAN channel. The permitted range is not verified (usually 1 to 13, depending on the country setting) |
| `MAX_STA_CONN_AP` | `4` | Maximum number of simultaneous clients. The upper limit comes from ESP-IDF (not verified) |
| `WIFI_AUTH_MODE` | `WIFI_AUTH_WPA2_PSK` | Encryption of the access point (text values see below) |
| `SAE_PWE_H2E` | `WPA3_SAE_PWE_BOTH` | WPA3 SAE method of the access point |
| `PMF_CFG` | `0` | `1`: clients **must** support protected management frames |
| `IP_ADDR` | `192.168.4.1` | IP address of the access point, always applies |
| `GATEWAY` | `192.168.4.1` | Gateway |
| `NETMASK` | `255.255.255.0` | Netmask |
| `MAIN_DNS_SERVER` | `192.168.4.1` | DNS server, only handed out to clients with `DHCP_SERVER=1` |
| `DHCP_SERVER` | `1` | DHCP server on or off |
| `hostname` | `espressif` | Set on the AP interface, empty or `espressif` means device name. A visible effect in AP mode is not verified, this value does not apply to mDNS |

!!! warning "An invalid channel or client count restarts the node"
    `WIFI_AP_CHANNEL` and `MAX_STA_CONN_AP` are passed to ESP-IDF without checking. If ESP-IDF rejects the value, the firmware aborts and restarts the node, possibly in a loop. In that case delete the file (see below).

**Text values of the enumerations**

The values are compared exactly: upper and lower case matter, and so do spaces around the value. An unknown value gives **no error**, but a fixed replacement value.

| Key | Allowed values | Replacement for unknown text |
| --- | --- | --- |
| `mode` | `WIFI_MODE_NULL`, `WIFI_MODE_STA`, `WIFI_MODE_AP`, `WIFI_MODE_APSTA` | `WIFI_MODE_AP` |
| `SCAN_METHOD` | `WIFI_FAST_SCAN`, `WIFI_ALL_CHANNEL_SCAN` | `WIFI_FAST_SCAN` |
| `WIFI_SCAN_AUTH_MODE_THRESHOLD`, `WIFI_AUTH_MODE` | `WIFI_AUTH_OPEN`, `WIFI_AUTH_WEP`, `WIFI_AUTH_WPA_PSK`, `WIFI_AUTH_WPA2_PSK`, `WIFI_AUTH_WPA_WPA2_PSK`, `WIFI_AUTH_WPA3_PSK`, `WIFI_AUTH_WPA2_WPA3_PSK`, `WIFI_AUTH_WAPI_PSK` | `WIFI_AUTH_WPA_WPA2_PSK` |
| `SAE_PWE_H2E` | `WPA3_SAE_PWE_UNSPECIFIED`, `WPA3_SAE_PWE_HUNT_AND_PECK`, `WPA3_SAE_PWE_HASH_TO_ELEMENT`, `WPA3_SAE_PWE_BOTH` | `WPA3_SAE_PWE_BOTH` |

For the encryption mode the replacement value is **not** the default: the default is `WIFI_AUTH_WPA2_PSK`, but a typo gives `WIFI_AUTH_WPA_WPA2_PSK`. Numbers and boolean values are read without range checking, IP addresses with `ip4addr_aton`.

### Getting an INI file onto the node

The firmware does not create the INI files itself. They are uploaded from outside:

1. Create the file locally, for example `ethernet.ini`.
2. Use the upload form on the node's web interface (`http://<ip>/`). Internally this is `POST /upload/<name>`, for example `/upload/ethernet.ini`.
3. Restart the node (Reboot button or `/reboot/`). `wlan.ini`, `ethernet.ini`, `functionalities.ini` and `device.ini` are only read at startup.

!!! warning "Upload only in the internal network"
    The upload uses unencrypted HTTP. For `wlan.ini` this sends the WLAN password (`WIFI_REMOTE_AP_PASSWORD`) over the network in clear text. Only upload in a network that all participants trust (for example the training network), not over foreign or public networks.

The firmware keeps `settings.ini` in memory and overwrites it with that state at the next save. A save can also happen between the upload and the restart (for example after an address change or a VT login) and replace the uploaded file with the old state. Restarting immediately only reduces this risk, it does not rule it out. To fix a value permanently, use `settingsReadOnly.ini` instead: it takes precedence and is never written by the firmware.

Deleting works via `/delete/<name>`. The deploy and preload scripts on this page do not touch INI files. The preload only deletes `.fboot` files and foreign manifests.

!!! warning "Pitfalls"
    - **Boolean values** such as `DHCP_CLIENT`, `SNTP_SYNC` or `DHCP_SERVER` must be `1` or `0`. `true` or `yes` is read as `0`. Writing `DHCP_CLIENT=true` gives you a static IP.
    - **Invalid values** are not reported. An invalid IP address results in `0.0.0.0`, an unknown value for `mode` falls back to `WIFI_MODE_AP`.
    - **Missing file:** The defaults apply. The log is no proof that the file is present: it also shows `Successfully loaded '/data/….ini'` when the file is missing.
    - **Wrong static IP:** The node is then only reachable at that address. To get back, upload a file with `DHCP_CLIENT=1` via another interface or reflash the file system. The S3's access point `192.168.4.1` is only an option if `mode` enables it (`WIFI_MODE_AP` or `WIFI_MODE_APSTA`). With `WIFI_MODE_STA`, as in the example above, there is no access point.

    The BOOT button does not reset anything: in the current state the firmware evaluates it neither at startup nor during operation. There are two ways to reset (from the code, not tested in operation): delete individual files via `/delete/<name>` and restart, after which the defaults apply for that file. Or use "Format" in the web interface (`/format_file_system/`): this deletes **everything** in `/data/`, including `.fboot`, `.libs.json`, `.elf`, `.iop`, licenses and `AuxAssignOfApp.txt`. Afterwards the defaults apply everywhere: on the S3 the access point `xx` at `192.168.4.1`, on Ethernet DHCP and, without a DHCP server, a link-local address.

### Further INI files

**`functionalities.ini`: which ISOBUS clients start**

    [functionalities]
    PART_6=1
    PART_10=1
    PART_10_TC_LOGIN_DELAY=0

| Key | Default | Effect |
| --- | --- | --- |
| `PART_6` | `1` | Log in the VT client (ISO 11783-6) |
| `PART_6_AUX_INPUT` | `0` | If `1`, the VT client logs in as an AUX input device instead of a normal VT client |
| `PART_10` | `0` | Log in the task controller client (ISO 11783-10) |
| `PART_10_TC_LOGIN_DELAY` | `0` | Delay of the TC login (number 0 to 65535, unit not verified) |
| `PART_13`, `PART_14` | `0` | are read but not evaluated anywhere, currently without effect |

`PART_6`, `PART_6_AUX_INPUT` and `PART_10` only take effect if the firmware was built with the matching option (VT client or task controller client). Write boolean values as `1` or `0`.

**`device.ini`: ISOBUS NAME**

    [ControlFunction01]
    Function=128
    Function_instance=1
    Identity_number=4711

| Key | Default | Meaning |
| --- | --- | --- |
| `Selfconfigurable` | `1` | Self-configurable |
| `Industry_group` | `2` | Industry group (2 = agriculture) |
| `Device_class` | `5` | Device class |
| `Device_class_instance` | `0` | Device class instance |
| `Function` | `128` | Function |
| `Function_instance` | `0` | Function instance |
| `ECU_instance` | `0` | ECU instance |
| `Manufacturer_code` | `1116` | Manufacturer code |
| `Identity_number` | `0` | If `0`, the firmware uses the device's serial number, otherwise this value |

!!! warning "Value ranges are not checked"
    The firmware does not check the bit widths of the ISO standard (for example 3 bits for the industry group, 21 bits for the identity number). The value goes into the NAME field unchanged. On a bus the NAMEs of all devices must differ. With `Identity_number=0` the serial number takes care of that. If you enter fixed values, you must watch this yourself.

**`settings.ini`: general settings**

    [mDNS]
    Hostname=workshop-left

    [SSDP]
    FriendlyName=Workshop left

    [CF-A]
    NODE1_SA=128
    bootTimeVT=120

| Section and key | Default | Meaning |
| --- | --- | --- |
| `[mDNS]` `Hostname` | empty (then `logibus-<MAC>`) | Hostname of the node, see above |
| `[SSDP]` `FriendlyName` | `logiBUS Controller` | Name used for device discovery on the network. Provisional, the key may still change |
| `[CF-A]` `NODE1_SA` | firmware's preferred address | Preferred ISOBUS source address. The firmware writes the value back if the node gets a different address during address claiming |
| `[CF-A]` `NODE2_SA` | as `NODE1_SA` | the same for the second node (whether the build contains it was not verified) |
| `[CF-A]` `preferredVT` | `0xFFFFFFFFFFFFFFFF` | NAME of the terminal used last. Written by the firmware |
| `[CF-A]` `bootTimeVT` | `120` | Boot time of the terminal. Written by the firmware |
| `[ObjectPool]` `file_de` | `pools/pool_de.iop` | no effect: the firmware reads the value but does not use it. Which pool is loaded is described below under `*.iop`. |
| `[ScalingTest]` | `enable=0` | Test and developer switch, not meant for class |

In addition, the 4diac function block `INI` and the `INI_A*` adapters read and write arbitrary section/key pairs in `settings.ini`. It is saved after every write and read.

The firmware writes `settings.ini` itself: every access with a default value adds a missing key together with its default, and it is saved at the next save operation (address change, VT login, access by the INI block). That is why the file comes into existence on its own over time, even without an upload.

**`settingsReadOnly.ini`: fixing values**

Same sections and keys as `settings.ini`, but read-only:

    [CF-A]
    NODE1_SA = 128
    bootTimeVT = 90

- If a key is present here, this value applies on every read.
- Write attempts on such a key are rejected (log: `write rejected, key is read-only`). The 4diac `INI` block then reports `Key is read-only`.
- When loading, the firmware deletes the same keys from `settings.ini`.
- The firmware never creates the file itself. If it is missing, that is not an error, and everything is writable.

!!! note "Being reworked"
    `[mDNS]` `Hostname` and the `hostname` keys of the network INIs (new hostname state) as well as `[SSDP]` `FriendlyName` are currently being reworked. According to the firmware state, the other files and keys are not.

### Further files in `/data/`

Besides the INI files, the `/data/` directory holds further files. Of these, the firmware only writes `settings.ini` and `AuxAssignOfApp.txt`. Everything else comes from outside, by upload or via the deploy and preload scripts.

| File | Content | Source |
| --- | --- | --- |
| `*.fboot` | Boot file of the 4diac application | deploy script or upload |
| `*.libs.json` | Manifest of the ELF libraries. Without a manifest, no ELF libraries are loaded. | deploy or preload script |
| `*.elf` | the ELF libraries, referenced by the manifest | deploy or preload script |
| `*.iop` | VT object pool (ISO 11783-6), the name is free | upload or deploy |
| `<poolname>.vis.json` | Mask visibility table, placed next to the pool with the pool's name | upload or deploy |
| `*.lic`, `*.key` | License and key files, read at startup | upload |
| `*.bin` | Firmware images | upload |
| `AuxAssignOfApp.txt` | preferred AUX assignment (see below) | the firmware, created at the terminal |

The firmware writes no log files to `/data/`. The file server computes SHA-256 hashes of the files in memory only (available at `/sha256/<file>`), no hash files are created.

!!! warning "For `.fboot`, `.libs.json` and `.iop` the alphabetically first file wins"
    If several files with the same extension are in `/data/`, the firmware uses only the alphabetically first one and warns in the log. An old file with a "smaller" name therefore silently beats a new one. Delete old files (`/delete/<name>`). The deploy script cleans up old boot files and manifests itself.

    Without an `.iop`, the firmware looks for `/data/DefaultPool.iop` and reports it as missing (`no object pool *.iop in /data`).

**`AuxAssignOfApp.txt`: preferred AUX assignment**

The file holds the "preferred assignment" (ISO 11783-6): which AUX functions of the object pool are assigned to which AUX input device (for example a joystick). It has nothing to do with `PART_6_AUX_INPUT`, that is, with the node itself acting as an AUX input device. It exists only in builds with a VT client.

- **Who writes it:** the firmware. If you assign at the terminal and mark the assignment as "store as preferred", the firmware rewrites the entire current assignment into the file. Uploading it is not intended.
- **Format:** text, one line per assignment, line ending CRLF. Six fields separated by spaces: manufacturer code of the input device, ModelIdentificationCode, AUX type, object ID of the AUX function, object ID of the AUX input (all decimal) and the 64-bit NAME of the input device as 16 hexadecimal characters.
- **If the file is missing:** There are no preferred assignments, and the assignment is made again at the terminal. The console shows `Error opening AuxAssignOfApp.txt`. This is not a crash.
- **Resetting the assignment:** delete the file (`/delete/AuxAssignOfApp.txt`). Afterwards the preferred assignment is missing until you assign again at the terminal and store it as preferred. Whether a restart is needed was not verified.
- **Invalid lines** are not reported: fields are read as numbers, nonsense gives 0.

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
