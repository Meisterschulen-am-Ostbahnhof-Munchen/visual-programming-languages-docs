# Deploy-Skripte und Launches

Diese Seite beschreibt, wie Programme aus der 4diac IDE auf die logiBUS®-Trainingsknoten (ESP32) gelangen und welche Skripte und Launch-Konfigurationen dafür im Trainingsprojekt vorhanden sind.

!!! info "Wo liegt was?"
    Alle Pfade beziehen sich auf den Ordner `Ventilsteuerung/` des Trainingsprojekts.

    - Python-Skripte: `scripts_central/`
    - Je Workspace (`test_AX`, `test_B`, `test_VV`): `scripts/` (`.bat` für Windows, `.sh` für Linux) und `Launches/` (`.launch`-Dateien für die 4diac IDE)

## Überblick: zwei Wege auf den Knoten

| Weg | Was wird übertragen | Wann |
| --- | --- | --- |
| **Online-Deploy** aus der 4diac IDE (`Deploy_App_*`) | Die Anwendung wird direkt in die laufende FORTE-Instanz geladen. | Schnelles Ausprobieren einer Übung. Nach einem Neustart ist die Anwendung weg. |
| **Boot-Datei-Deploy** (Python-Skripte) | `.fboot`, Bibliotheks-Manifest (`.libs.json`) und die benötigten ELF-Bibliotheken werden per HTTP auf den Knoten kopiert. | Dauerhafte Installation. FORTE lädt die Boot-Datei beim nächsten Start. |

Für den Online-Deploy muss der Knoten vorher mit der ELF-Grundausstattung vorbereitet sein (siehe [Knoten vorbereiten](#knoten-vorbereiten-preload)). Sonst meldet FORTE für Bausteine, deren Bibliothek fehlt, `UNSUPPORTED_TYPE`.

## Python-Skripte in `scripts_central/`

Alle Skripte sind reines Python (nur Standardbibliothek, keine `pip`-Installation nötig). Die Befehlsbeispiele auf dieser Seite sind aus dem Ordner `Ventilsteuerung/` aufzurufen. Die `.bat`-Skripte und Launches setzen das Arbeitsverzeichnis selbst.

### Deploy und Bibliotheken

| Skript | Aufgabe |
| --- | --- |
| `make_libs_manifest.py` | Erzeugt lokal `boot-files/<Boot-Datei>.libs.json`. Kein Netzwerkzugriff. Die Option `--out <Pfad>` schreibt das Manifest an einen anderen Ort (Testlauf). |
| `make_4diac_training1_deploy.py` | Lädt die Boot-Datei, das Manifest und die benötigten ELF-Bibliotheken auf die Knoten aus `NODE_ORDER`. |
| `make_4diac_training1_deploy_dido.py` | Deploy für den DIDO-Tester: wie oben, zusätzlich VT-Pool (`DefaultPool.iop`), Sichtbarkeitstabelle (`DefaultPool.vis.json`) und Web-Client (`apixon-diodo.html`). Zielknoten als Argument, Standard `logibus.local`. |
| `make_4diac_training1_elf_preload.py` | Bereitet einen Knoten für den Online-Deploy vor (nur Grundausstattung, keine Boot-Datei). |
| `deploy_common.py` | Kein eigenes Skript, sondern gemeinsames Modul: Zuordnung Knoten-Adresse zu Boot-Datei (`NODE_BASES`, `NODE_ORDER`), Pfade der Boot-Dateien und die Liste der Grundausstattung (`PRELOAD_LIBS`). |
| `elf_libs_manifest_lib.py` | Logik hinter dem Manifest: welcher 4diac-Typ zu welcher Bibliothek gehört, `requires` aus der `MANIFEST.MF`, Architektur der Knoten (`riscv32` oder `xtensa`) und die Firmware-Grenzen. |

### Pool-Erzeugung und Prüfungen

| Skript | Aufgabe |
| --- | --- |
| `compile_iso_designer_project.py` | Übersetzt ein ISO-Designer-Projekt über die Kommandozeile (`ISODesigner.exe /Compile`). Pflichtargument `--pool-dir`. Nur Windows, mit installiertem ISO-Designer. |
| `GcfScript.py` | Erzeugt aus `DefaultPool.iop.h` (und optional `DefaultPool.jop`) die `.gcf`-Konstantendateien für 4diac. |
| `list_mask_objects.py` | Liest die Masken des Pools und schreibt die Sichtbarkeitstabellen (`.vis.csv`, `.vis.json`). |
| `check_mixed_numeric_pool_imports.py` | Findet `.SUB`-Dateien, die VT-Konstanten aus mehreren verschiedenen Pools importieren. |

!!! warning "Generierte `.gcf`-Dateien nicht von Hand ändern"
    `GcfScript.py` baut die `.gcf`-Dateien jedes Mal komplett neu aus `DefaultPool.iop.h`. Von Hand ergänzte Konstanten gehen beim nächsten Lauf verloren. Änderungen gehören in den ISO-Designer, danach den Build-Lauf wiederholen.

## Ablauf eines Boot-Datei-Deploys

`make_4diac_training1_deploy.py` arbeitet die Knoten nacheinander ab:

1. **Dateien prüfen.** Fehlt eine Boot-Datei (`boot-files/…fboot`), bricht das Skript ab. Die Boot-Datei muss vorher aus der 4diac IDE exportiert sein. Das Skript baut selbst nichts.
2. **Knoten prüfen.** Der Name wird einmal aufgelöst. Erlaubt sind nur Knoten im internen Netz (`10.x`, `172.16`–`172.31`, `192.168.x`, `169.254.x`, `*.local`). Nicht erreichbare Knoten werden übersprungen.
3. **Architektur prüfen.** Die Architektur des Knotens muss zu den ELF-Bibliotheken passen, sonst wird für diesen Knoten nichts hochgeladen.
4. **Boot-Datei hochladen** (`POST /upload/<datei>`). Hat der Knoten die neue Firmware, wird die Datei über den SHA-256-Hash verglichen. Unveränderte Dateien werden übersprungen, hochgeladene Dateien werden anschließend verifiziert.
5. **Alte Boot-Dateien entfernen**, die zu diesem Knoten gehören.
6. **Manifest und ELF-Bibliotheken.** Das Skript ermittelt aus der Boot-Datei die benötigten Bibliotheken samt `requires`, räumt alte Versionen in `elf-libs/` auf und lädt fehlende ELF-Dateien nach `elf-libs/` hoch.
7. **Manifest zuletzt hochladen.** Ist mindestens ein ELF-Upload fehlgeschlagen, wird das Manifest bewusst nicht hochgeladen.

Grenzen der Firmware: höchstens 64 Bibliotheken je Knoten und höchstens 8 `requires` je Bibliothek. Wird eine Grenze überschritten, meldet das Skript eine Warnung.

!!! warning "Das Skript startet den Knoten nicht neu"
    Neue Dateien werden erst nach einem Neustart aktiv, zum Beispiel über den Reboot-Button auf `http://<ip>/`. Meldet die Zusammenfassung einen Fehler für einen Knoten, diesen **nicht** neu starten, sondern das Deploy wiederholen.

!!! note "Nur für das Übungsnetz"
    Die Skripte übertragen unverschlüsselt per HTTP und ohne Anmeldung. Das ist für das abgeschirmte Übungsnetz gedacht. In produktiven IoT/OT-Systemen braucht es Transportverschlüsselung (HTTPS/TLS) und Zugriffskontrolle.

!!! warning "Es gibt keinen Trockenlauf"
    Das Skript lädt wirklich auf den Knoten hoch. Vor wiederholten Testläufen den freien Speicher unter `http://<ip>/space/` prüfen. Ein fast volles Dateisystem kann bei weiteren Uploads beschädigt werden und wird beim nächsten Start neu formatiert. Dabei sind alle Dateien weg.

### Knoten vorbereiten (Preload)

`make_4diac_training1_elf_preload.py` kopiert die Grundausstattung (`PRELOAD_LIBS` in `deploy_common.py`, plus deren `requires`) nach `/data/elf-libs/` und legt ein eigenes Manifest ohne Boot-Datei an. Alle anderen Manifeste und alle `.fboot`-Dateien auf dem Knoten werden dabei **gelöscht**: FORTE startet danach leer, aber mit geladenen Bibliotheken, und die Übung kommt per Online-Deploy aus der IDE.

    python scripts_central/make_4diac_training1_elf_preload.py                                 # logibus.local
    python scripts_central/make_4diac_training1_elf_preload.py 192.168.178.45   # bestimmter Knoten

Nicht zur Grundausstattung gehören `Funk`, `DataPanel`, `BlinkMarine` und `logiBUS_bosch`. Das Board „Trainer“ hat kein CAN2. Auch hier gilt: Neue Dateien werden erst nach einem Neustart des Knotens aktiv.

Ein späteres normales Deploy ersetzt das Preload-Manifest durch sein eigenes. Die ELF-Dateien der Grundausstattung bleiben liegen und werden per Hash übersprungen.

Die Knotenadressen stehen in `deploy_common.py` und `elf_libs_manifest_lib.py`. Wird ein Knoten ersetzt, müssen sie dort angepasst werden.

## Knoten finden und IP-Adresse einstellen

### Hostname und mDNS

Ein Knoten meldet sich per mDNS unter einem Namen mit der Endung `.local`. Die Skripte nutzen `logibus.local` als Standardziel, wenn kein Knoten angegeben wird.

- Jede Platine heißt `logibus-<xxxxxx>.local`. `<xxxxxx>` sind die letzten drei Bytes der MAC-Adresse, zum Beispiel `logibus-3a7f21.local`. Der Name ist damit je Platine eindeutig.
- Dieser Name ist auch der DHCP-Hostname auf allen Schnittstellen und der Hostname des OPC-UA-Endpoints (`opc.tcp://logibus-xxxxxx.local:4840`).
- `logibus.local` bleibt als Zusatzname erhalten, aber nur, wenn **eine** Platine im Netz ist. Melden zwei Geräte den Namen, behält ihn die Platine mit der niedrigeren IP.
- Wer einen eigenen Namen will, trägt ihn in der `/data/settings.ini` ein:

        [mDNS]
        Hostname=meine-platine

  Ist der Eintrag leer oder steht dort der alte Wert `logibus`, gilt der automatische Name. Ein eigener Name wird auf die Zeichen `A–Z`, `a–z`, `0–9` und `-` bereinigt.

!!! warning "Ältere Firmware"
    Auf Geräten mit älterer Firmware heißen **alle** Platinen `logibus.local`. Welche Platine antwortet, ist dann Zufall. In diesem Fall nur eine Platine gleichzeitig anschließen oder den Knoten über seine IP-Adresse ansprechen. Der DHCP-Hostname lautet dort `espressif-eth-int`, `espressif-eth-spi1`, `espressif-eth-spi2` beziehungsweise `espressif`.

!!! note "Stand der Firmware"
    Die eindeutigen Namen sind eine neuere Firmware-Änderung. Sie war beim Schreiben dieser Seite noch nicht auf Hardware getestet. Im Zweifel mit `ping logibus.local` oder der Weboberfläche des Routers prüfen, unter welchem Namen und welcher IP sich der Knoten meldet.

### Welche Adresse bekommt der Knoten?

1. **DHCP** (Standard, `DHCP_CLIENT=1`): Der Knoten bekommt seine Adresse vom DHCP-Server im Netz.
2. **Link-Local:** Antwortet nach zwei Versuchen kein DHCP-Server, vergibt sich der Knoten selbst eine Adresse aus `169.254.x.x`. Das gilt nur mit `DHCP_CLIENT=1`. Fragt der DHCP-Client weiter und taucht ein Server auf, übernimmt der Knoten dessen Adresse.
3. **Statisch** (`DHCP_CLIENT=0`): Die Adresse steht in der INI-Datei.

### INI-Dateien

Die Einstellungen liegen als INI-Dateien im Verzeichnis `/data/` des Knotens:

| Datei | Inhalt | Gilt für |
| --- | --- | --- |
| `/data/ethernet.ini` | Ethernet: Abschnitte `[ETH_INT]` (internes Ethernet), `[ETH_SPI1]` und `[ETH_SPI2]` (SPI-Ethernet-Chips, S3-Boards mit `_1ETH` beziehungsweise `_2ETH`) | Builds mit Ethernet |
| `/data/wlan.ini` | WLAN-Client und Access Point: `[general]`, `[WIFI_STA]`, `[WIFI_AP]` | nur S3 |
| `/data/settings.ini` | Allgemeine Einstellungen, darunter `[mDNS]` mit `Hostname` | alle |

Das interne Ethernet (`[ETH_INT]`) haben P4 (NodeISO20) und S31 (Trainer20). Diese beiden haben kein WLAN und damit keinen Access Point.

**Statische IP am Ethernet:**

    [ETH_INT]
    DHCP_CLIENT=0
    IP_ADDR=192.168.1.50
    NETMASK=255.255.255.0
    GATEWAY=192.168.1.1
    MAIN_DNS_SERVER=192.168.1.1

`IP_ADDR`, `NETMASK`, `GATEWAY` und die DNS-Server wirken nur bei `DHCP_CLIENT=0`. Weitere Schlüssel je Abschnitt: `BACKUP_DNS_SERVER`, `FALLBACK_DNS_SERVER`, `hostname` (DHCP-Hostname), `SNTP_SYNC`, `SNTP_SERVER_0` und `TZ`. Fehlende Schlüssel bekommen ihren Standardwert. Die Standard-IP von `[ETH_INT]` ist `192.168.4.17`, bei `[ETH_SPI1]` aus dem Netz `192.168.5.x` und bei `[ETH_SPI2]` aus `192.168.6.x`.

**WLAN-Client mit DHCP (S3):**

    [general]
    mode=WIFI_MODE_STA

    [WIFI_STA]
    WIFI_REMOTE_AP_SSID=MeinNetz
    WIFI_REMOTE_AP_PASSWORD=geheim
    DHCP_CLIENT=1

Mögliche Werte für `mode`: `WIFI_MODE_AP` (Standard), `WIFI_MODE_STA`, `WIFI_MODE_APSTA` und `WIFI_MODE_NULL`.

!!! warning "Standardmäßig spannt jeder S3 einen Access Point auf"
    Ohne `wlan.ini` läuft ein S3 als Access Point mit der SSID `xx`, dem Passwort `esp32_pwd`, der IP `192.168.4.1` und einem DHCP-Server. Mehrere S3 ohne eigene `wlan.ini` haben also dieselbe SSID und dieselbe IP. Im Unterricht jedem Knoten eine eigene `wlan.ini` geben oder nur einen gleichzeitig einschalten.

### INI-Datei auf den Knoten bringen

Die Firmware legt die INI-Dateien nicht selbst an. Sie werden von außen hochgeladen:

1. Datei lokal anlegen, zum Beispiel `ethernet.ini`.
2. Auf der Weboberfläche des Knotens (`http://<ip>/`) das Upload-Formular benutzen. Intern ist das `POST /upload/<name>`, zum Beispiel `/upload/ethernet.ini`.
3. Knoten neu starten (Reboot-Button oder `/reboot/`). Die Dateien werden nur beim Start gelesen.

Löschen geht über `/delete/<name>`. Die Deploy- und Preload-Skripte dieser Seite fassen INI-Dateien nicht an. Der Preload löscht nur `.fboot`-Dateien und fremde Manifeste.

!!! warning "Stolperfallen"
    - **Wahrheitswerte** wie `DHCP_CLIENT`, `SNTP_SYNC` oder `DHCP_SERVER` müssen `1` oder `0` sein. `true` oder `yes` wird als `0` gelesen. Wer `DHCP_CLIENT=true` schreibt, bekommt eine statische IP.
    - **Ungültige Werte** werden nicht gemeldet. Eine ungültige IP-Adresse ergibt `0.0.0.0`, ein unbekannter Wert bei `mode` fällt auf `WIFI_MODE_AP` zurück.
    - **Fehlende Datei:** Es gelten die Standardwerte. Im Log steht `Can't load '/data/ethernet.ini', using defaults`.
    - **Falsche statische IP:** Der Knoten ist dann nur noch unter dieser Adresse erreichbar. Zurück kommt man, indem man eine Datei mit `DHCP_CLIENT=1` über eine andere Schnittstelle hochlädt (beim S3 zum Beispiel über den Access Point `192.168.4.1`) oder das Dateisystem neu flasht.

## Launch-Konfigurationen in der 4diac IDE

Die Dateien in `Launches/` erscheinen in der IDE unter *Run As* beziehungsweise *Run Configurations*. Es gibt drei Arten:

| Art | Dateiname | Was sie tut |
| --- | --- | --- |
| **External Tool** | `RunSkript_<Name>.bat.launch` | Startet das gleichnamige Skript aus `scripts/`. Arbeitsverzeichnis ist `scripts/` des Workspaces. |
| **4diac-Deployment** | `Deploy_App_<Name>.launch` | Online-Deploy des System-Eintrags (`.sys`) auf die im Launch ausgewählten Geräte und Ressourcen. |
| **Launch-Gruppe** | `Launch_Deploy_App_<Name>.launch` | Führt mehrere Launches nacheinander aus. |

### Workspace `test_AX`

| Launch / Skript | Inhalt |
| --- | --- |
| `RunSkript_DeployAX.bat.launch` | `RunSkript_DeployAX.bat`: erst `make_libs_manifest.py`, dann `make_4diac_training1_deploy.py` (Boot-Datei-Deploy). |
| `RunSkript_MakeLibsManifestAX.bat.launch` | Nur das Manifest erzeugen (lokal). |
| `RunSkript_PreloadELF_AX.bat.launch` | Knoten vorbereiten (Preload, siehe oben). |
| `RunSkript_CheckMixedPoolImports_AX.bat.launch` | Prüfung auf gemischte Pool-Importe. Für Linux gibt es `RunSkript_CheckMixedPoolImports_AX.sh`. |
| `RunSkript_Build<Pool>_AX.bat.launch` | Pool bauen: ISO-Designer-Projekt übersetzen, alte `.gcf` löschen, `GcfScript.py` und `list_mask_objects.py` ausführen. |
| `RunSkript_ALL_AX.bat.launch` | Führt alle Build-Skripte nacheinander aus. Bei einem Fehler bricht die Kette ab. |
| `Deploy_App_AX.launch` | Online-Deploy von `test_AX.sys` auf `FORTE_PC_AX` und `EMB_RES_AX`. |
| `Launch_Deploy_App_AX.launch` | Gruppe: erst `RunSkript_BuildAX.bat` (wartet auf das Ende), dann `Deploy_App_AX`. |
| `RunSkript_Deploy_DIDO_AX.bat` (ohne Launch) | `make_4diac_training1_deploy_dido.py`. Argumente werden durchgereicht, zum Beispiel eine Adresse statt `logibus.local`. |

Die Build-Skripte gibt es für diese Pools: `BuildAX` (Standardpool), `BuildEmpty`, `BuildPWM`, `BuildPWM12`, `BuildTECU`, `BuildHorse`, `BuildDIDO`, `BuildJoystick`, `BuildTC_SC`, `BuildScroll`, `BuildPI`, `BuildAI`, `BuildAI_Calibrate_2P`, `BuildAI_Calibrate_3P`, `BuildDreieck`, `BuildHystereseHorizontal`, `BuildHystereseVertikal`.

### Workspaces `test_B` und `test_VV`

- `test_B`: Die Skripte heißen `RunSkript_Workspace_<Pool>_B.bat` (und `.sh`). `RunSkript_ALL_B.bat` baut alle Pools. `Launch_Deploy_App_B` führt zuerst `RunSkript_ALL_B.bat` aus und danach `Deploy_App_B` (Ziel `FORTE_PC_B`).
- `test_VV`: Ein Skript `RunSkript_Workspace_VV.bat`. Die `Deploy_App_*`-Launches gehören zu den OPC-UA-Beispielen (`CLIENT_SERVER`, `OPC_UA_RES`, `OPC_UA_SUB`, `PUBLISH_SUBSCRIBE` und Varianten) und laden auf mehrere Geräte (zum Beispiel `FORTE_PC_A` und `FORTE_PC_B`). Die zugehörigen `Launch_Deploy_App_*`-Gruppen enthalten nur den Deploy.

!!! note "Linux"
    Die `.sh`-Varianten führen nur `GcfScript.py` aus. Das Übersetzen des ISO-Designer-Projekts braucht Windows, weil `compile_iso_designer_project.py` die `ISODesigner.exe` aufruft. Der Pfad zur Installation ist im Skript festgelegt (ISO-Designer 5.7.2).

## Typische Abläufe

**Neue Übung schnell testen (Online-Deploy)**

1. Einmalig: `RunSkript_PreloadELF_AX` ausführen und den Knoten neu starten. **Achtung:** Das löscht alle `.fboot`-Dateien und Manifeste auf dem Knoten. Eine dauerhaft installierte Übung ist danach weg.
2. In der IDE `Deploy_App_AX` ausführen.

**Übung dauerhaft installieren**

1. Boot-Datei aus der 4diac IDE exportieren.
2. `RunSkript_DeployAX` ausführen.
3. Nur wenn das Deploy ohne Fehler endet: Knoten neu starten (Reboot-Button auf `http://<ip>/`). Bei einem Fehler das Deploy wiederholen und erst danach neu starten.

**Pool im ISO-Designer geändert**

1. Passendes `RunSkript_Build…` ausführen (oder `RunSkript_ALL_AX`).
2. Danach die 4diac IDE aktualisieren und neu deployen.
