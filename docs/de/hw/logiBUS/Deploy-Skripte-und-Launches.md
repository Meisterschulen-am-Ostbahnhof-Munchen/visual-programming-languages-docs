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
| `/data/settings.ini` | Allgemeine Einstellungen (Hostname, ISOBUS-Adresse, Objektpool, eigene Werte aus 4diac) | alle |
| `/data/settingsReadOnly.ini` | Fest vorgegebene Werte, die Vorrang vor `settings.ini` haben | alle |
| `/data/functionalities.ini` | Welche ISOBUS-Clients sich anmelden (VT, AUX, TC) | alle |
| `/data/device.ini` | ISOBUS-NAME der Control Function | alle |

Das sind alle INI-Dateien der Firmware, es gibt keine weiteren. Alle liegen im Dateisystem des Knotens unter `/data/`.

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

### `ethernet.ini`: alle Schlüssel

Die drei Abschnitte `[ETH_INT]`, `[ETH_SPI1]` und `[ETH_SPI2]` haben dieselben Schlüssel. Sie unterscheiden sich nur in den Standardwerten. Die Firmware liest nur die hier genannten Schlüssel, weitere gibt es nicht. Angaben mit „ungeprüft“ sind nicht im Firmware-Code belegt.

| Schlüssel | Standard `ETH_INT` | Standard `ETH_SPI1` | Standard `ETH_SPI2` | Wirkung |
| --- | --- | --- | --- | --- |
| `DHCP_CLIENT` | `1` | `1` | `1` | `1`: Adresse per DHCP, `0`: statische Adresse aus dieser Datei |
| `IP_ADDR` | `192.168.4.17` | `192.168.5.17` | `192.168.6.17` | Statische IP-Adresse |
| `NETMASK` | `255.255.255.0` | `255.255.255.0` | `255.255.255.0` | Netzmaske |
| `GATEWAY` | `192.168.4.1` | `192.168.5.1` | `192.168.6.1` | Gateway |
| `MAIN_DNS_SERVER` | `192.168.4.1` | `192.168.5.1` | `192.168.6.1` | Erster DNS-Server |
| `BACKUP_DNS_SERVER` | `0.0.0.0` | `0.0.0.0` | `0.0.0.0` | Zweiter DNS-Server |
| `FALLBACK_DNS_SERVER` | `0.0.0.0` | `0.0.0.0` | `0.0.0.0` | Dritter DNS-Server |
| `hostname` | `espressif-eth-int` | `espressif-eth-spi1` | `espressif-eth-spi2` | DHCP-Hostname dieses Anschlusses, **nicht** der mDNS-Name (siehe unten) |
| `SNTP_SYNC` | `0` | `0` | `0` | `1`: Uhrzeit per SNTP holen |
| `SNTP_SERVER_0` | `pool.ntp.org` | `pool.ntp.org` | `pool.ntp.org` | SNTP-Server |
| `TZ` | `CET-1CEST,M3.5.0,M10.5.0/3` | dito | dito | Zeitzone als POSIX-TZ-Text |

- `IP_ADDR`, `NETMASK`, `GATEWAY`, `MAIN_DNS_SERVER` und `BACKUP_DNS_SERVER` gelten nur bei `DHCP_CLIENT=0`. `FALLBACK_DNS_SERVER` wird auch bei DHCP gesetzt.
- `hostname`: Ein leerer Wert oder der alte Standardwert (`espressif-eth-int`, `espressif-eth-spi1`, `espressif-eth-spi2`) bedeutet, dass der Gerätename benutzt wird. Der mDNS-Name hängt nicht an diesem Schlüssel, siehe [Hostname und mDNS](#hostname-und-mdns).
- **SNTP und `TZ` gelten faktisch für den ganzen Knoten, nicht je Anschluss.** Der erste Anschluss mit `SNTP_SYNC=1` startet SNTP mit seinem Server und seiner Zeitzone, alle weiteren werden übersprungen. Lief schon SNTP aus der `wlan.ini` (WLAN startet vor Ethernet), gewinnt das WLAN. Ohne `SNTP_SYNC=1` irgendwo wird `TZ` nirgends gesetzt.

### `wlan.ini`: alle Schlüssel

Die Datei gibt es nur beim S3. Auch hier liest die Firmware nur die genannten Schlüssel. Der Abschnitt `[WIFI_STA]` gilt bei `mode=WIFI_MODE_STA` und `WIFI_MODE_APSTA`, der Abschnitt `[WIFI_AP]` bei `WIFI_MODE_AP` und `WIFI_MODE_APSTA`.

**`[general]`**

| Schlüssel | Standard | Wirkung |
| --- | --- | --- |
| `mode` | `WIFI_MODE_AP` | `WIFI_MODE_NULL`, `WIFI_MODE_STA`, `WIFI_MODE_AP` oder `WIFI_MODE_APSTA` |

**`[WIFI_STA]`** (Knoten als WLAN-Client)

| Schlüssel | Standard | Wirkung |
| --- | --- | --- |
| `WIFI_REMOTE_AP_SSID` | `WLAN-SSID` | Name des WLAN, mit dem sich der Knoten verbindet |
| `WIFI_REMOTE_AP_PASSWORD` | `PASSWORD` | Passwort dieses WLAN |
| `SCAN_METHOD` | `WIFI_FAST_SCAN` | `WIFI_FAST_SCAN` oder `WIFI_ALL_CHANNEL_SCAN` |
| `MAXIMUM_RETRY` | `5` | Wird an ESP-IDF (`failure_retry_cnt`) übergeben. Nach ESP-IDF: Wiederholungen je Access Point beim Verbinden, bevor der nächste versucht wird (ungeprüft) |
| `CNN_MAXIMUM_RETRY` | `5` | Eigene Grenze der Firmware: Bei jeder Trennung wird neu verbunden, bis diese Zahl erreicht ist. Danach verbindet die Firmware bis zum nächsten Neustart **nicht mehr** neu. Bei einer IP-Adresse wird der Zähler zurückgesetzt. Beim Start wartet die Firmware, bis die Verbindung steht oder die Versuche aufgebraucht sind |
| `WIFI_SCAN_AUTH_MODE_THRESHOLD` | `WIFI_AUTH_WPA2_PSK` | Schwächste Verschlüsselung, die der Knoten akzeptiert (Textwerte siehe unten) |
| `RSSIThreshold` | `-127` | Mindest-Signalstärke in dBm. `-127` bedeutet keine Grenze (ungeprüft) |
| `SAE_PWE_H2E` | `WPA3_SAE_PWE_BOTH` | WPA3-SAE-Verfahren (Textwerte siehe unten) |
| `SAE_H2E_IDENTIFIER` | leer | Wird an ESP-IDF übergeben, nach ESP-IDF der Passwort-Identifier bei WPA3-H2E (ungeprüft) |
| `DHCP_CLIENT` | `1` | `1`: Adresse per DHCP, `0`: statische Adresse aus dieser Datei |
| `IP_ADDR` | `192.168.4.16` | Statische IP-Adresse |
| `NETMASK` | `255.255.255.0` | Netzmaske |
| `GATEWAY` | `192.168.4.1` | Gateway |
| `MAIN_DNS_SERVER` | `192.168.4.1` | Erster DNS-Server |
| `BACKUP_DNS_SERVER` | `0.0.0.0` | Zweiter DNS-Server |
| `FALLBACK_DNS_SERVER` | `0.0.0.0` | Dritter DNS-Server |
| `hostname` | `espressif` | DHCP-Hostname im WLAN-Client-Netz. Leer oder `espressif` bedeutet, dass der Gerätename benutzt wird |
| `SNTP_SYNC` | `0` | `1`: SNTP starten. Die Firmware wartet dann bis zu 10 × 2 s auf die Uhrzeit, **vor** dem WLAN-Start. Der Start verzögert sich um bis zu etwa 18 s |
| `SNTP_SERVER_0` | `pool.ntp.org` | SNTP-Server |
| `TZ` | `CET-1CEST,M3.5.0,M10.5.0/3` | Zeitzone als POSIX-TZ-Text, wird nach der SNTP-Synchronisation gesetzt |
| `STATIC_DNS_RESOLVE_TEST` | `0` | Diagnose: Bei `1` wird einmal `RESOLVE_DOMAIN` aufgelöst und das Ergebnis ins Log geschrieben. Das passiert **vor** dem WLAN-Start, ohne Verbindung schlägt der Test praktisch immer fehl |
| `RESOLVE_DOMAIN` | `www.google.com` | Domain für diesen Test |

!!! warning "Das Log zeigt das WLAN-Passwort im Klartext"
    Beim Verbinden schreibt die Firmware SSID **und** Passwort im Klartext ins Log (`connected to ap SSID:… password:…`), ebenso bei einem Fehlschlag. Logs mit `wlan.ini`-Zugangsdaten deshalb nicht weitergeben.

**`[WIFI_AP]`** (Knoten als Access Point)

| Schlüssel | Standard | Wirkung |
| --- | --- | --- |
| `WIFI_AP_SSID` | `xx` | Name des Access Points. Bei genau `xx` (dem Standard) setzt die Firmware die ersten zwei Bytes der SSID auf `0xFF`: Die SSID besteht dann aus zwei nicht druckbaren Bytes und ist nicht `xx`. Die Anzeige auf Handy oder PC ist ungeprüft |
| `WIFI_AP_PASSWORD` | `esp32_pwd` | Passwort. Ist es leer, wird ein **offenes Netz** erzwungen (`WIFI_AUTH_OPEN`) |
| `WIFI_AP_CHANNEL` | `1` | WLAN-Kanal. Der zulässige Bereich ist ungeprüft (üblich 1 bis 13, je nach Ländereinstellung) |
| `MAX_STA_CONN_AP` | `4` | Höchstzahl gleichzeitiger Clients. Die Obergrenze kommt aus ESP-IDF (ungeprüft) |
| `WIFI_AUTH_MODE` | `WIFI_AUTH_WPA2_PSK` | Verschlüsselung des Access Points (Textwerte siehe unten) |
| `SAE_PWE_H2E` | `WPA3_SAE_PWE_BOTH` | WPA3-SAE-Verfahren des Access Points |
| `PMF_CFG` | `0` | `1`: Clients **müssen** Protected Management Frames können |
| `IP_ADDR` | `192.168.4.1` | IP-Adresse des Access Points, gilt immer |
| `GATEWAY` | `192.168.4.1` | Gateway |
| `NETMASK` | `255.255.255.0` | Netzmaske |
| `MAIN_DNS_SERVER` | `192.168.4.1` | DNS-Server, wird nur bei `DHCP_SERVER=1` an die Clients verteilt |
| `DHCP_SERVER` | `1` | DHCP-Server ein oder aus |
| `hostname` | `espressif` | Wird auf das AP-Interface gesetzt, leer oder `espressif` bedeutet Gerätename. Eine sichtbare Wirkung im AP-Modus ist ungeprüft, für mDNS gilt dieser Wert nicht |

!!! warning "Ungültiger Kanal oder Client-Zahl startet den Knoten neu"
    `WIFI_AP_CHANNEL` und `MAX_STA_CONN_AP` werden ohne Prüfung an ESP-IDF übergeben. Lehnt ESP-IDF den Wert ab, bricht die Firmware ab und startet den Knoten neu, unter Umständen in einer Schleife. In dem Fall die Datei löschen (siehe unten).

**Textwerte der Aufzählungen**

Die Werte werden exakt verglichen: Groß- und Kleinschreibung zählen, Leerzeichen um den Wert ebenfalls. Ein unbekannter Wert ergibt **keinen Fehler**, sondern einen festen Ersatzwert.

| Schlüssel | Erlaubte Werte | Ersatzwert bei unbekanntem Text |
| --- | --- | --- |
| `mode` | `WIFI_MODE_NULL`, `WIFI_MODE_STA`, `WIFI_MODE_AP`, `WIFI_MODE_APSTA` | `WIFI_MODE_AP` |
| `SCAN_METHOD` | `WIFI_FAST_SCAN`, `WIFI_ALL_CHANNEL_SCAN` | `WIFI_FAST_SCAN` |
| `WIFI_SCAN_AUTH_MODE_THRESHOLD`, `WIFI_AUTH_MODE` | `WIFI_AUTH_OPEN`, `WIFI_AUTH_WEP`, `WIFI_AUTH_WPA_PSK`, `WIFI_AUTH_WPA2_PSK`, `WIFI_AUTH_WPA_WPA2_PSK`, `WIFI_AUTH_WPA3_PSK`, `WIFI_AUTH_WPA2_WPA3_PSK`, `WIFI_AUTH_WAPI_PSK` | `WIFI_AUTH_WPA_WPA2_PSK` |
| `SAE_PWE_H2E` | `WPA3_SAE_PWE_UNSPECIFIED`, `WPA3_SAE_PWE_HUNT_AND_PECK`, `WPA3_SAE_PWE_HASH_TO_ELEMENT`, `WPA3_SAE_PWE_BOTH` | `WPA3_SAE_PWE_BOTH` |

Beim Verschlüsselungsmodus ist der Ersatzwert **nicht** der Standardwert: Der Standard ist `WIFI_AUTH_WPA2_PSK`, ein Tippfehler ergibt aber `WIFI_AUTH_WPA_WPA2_PSK`. Zahlen und Wahrheitswerte werden ohne Bereichsprüfung gelesen, IP-Adressen mit `ip4addr_aton`.

### INI-Datei auf den Knoten bringen

Die Firmware legt die INI-Dateien nicht selbst an. Sie werden von außen hochgeladen:

1. Datei lokal anlegen, zum Beispiel `ethernet.ini`.
2. Auf der Weboberfläche des Knotens (`http://<ip>/`) das Upload-Formular benutzen. Intern ist das `POST /upload/<name>`, zum Beispiel `/upload/ethernet.ini`.
3. Knoten neu starten (Reboot-Button oder `/reboot/`). `wlan.ini`, `ethernet.ini`, `functionalities.ini` und `device.ini` werden nur beim Start gelesen.

!!! warning "Upload nur im internen Netz"
    Der Upload läuft über unverschlüsseltes HTTP. Bei `wlan.ini` geht damit das WLAN-Passwort (`WIFI_REMOTE_AP_PASSWORD`) im Klartext über das Netz. Nur in einem Netz hochladen, dem alle Teilnehmer vertrauen (zum Beispiel das Übungsnetz), nicht über fremde oder öffentliche Netze.

Die `settings.ini` hält die Firmware im Speicher und überschreibt sie beim nächsten Speichervorgang mit diesem Stand. Ein Speichervorgang kann auch zwischen Upload und Neustart passieren (zum Beispiel nach einer Adressänderung oder einem VT-Login) und die hochgeladene Datei durch den alten Stand ersetzen. Sofortiges Neustarten verkleinert dieses Risiko nur, es schließt es nicht aus. Wer einen Wert fest vorgeben will, nimmt besser die `settingsReadOnly.ini`: Sie hat Vorrang und wird von der Firmware nie geschrieben.

Löschen geht über `/delete/<name>`. Die Deploy- und Preload-Skripte dieser Seite fassen INI-Dateien nicht an. Der Preload löscht nur `.fboot`-Dateien und fremde Manifeste.

!!! warning "Stolperfallen"
    - **Wahrheitswerte** wie `DHCP_CLIENT`, `SNTP_SYNC` oder `DHCP_SERVER` müssen `1` oder `0` sein. `true` oder `yes` wird als `0` gelesen. Wer `DHCP_CLIENT=true` schreibt, bekommt eine statische IP.
    - **Ungültige Werte** werden nicht gemeldet. Eine ungültige IP-Adresse ergibt `0.0.0.0`, ein unbekannter Wert bei `mode` fällt auf `WIFI_MODE_AP` zurück.
    - **Fehlende Datei:** Es gelten die Standardwerte. Das Log ist dafür kein Beweis, dass die Datei da ist: Es steht auch bei fehlender Datei `Successfully loaded '/data/….ini'`.
    - **Falsche statische IP:** Der Knoten ist dann nur noch unter dieser Adresse erreichbar. Zurück kommt man, indem man eine Datei mit `DHCP_CLIENT=1` über eine andere Schnittstelle hochlädt oder das Dateisystem neu flasht. Der Access Point `192.168.4.1` des S3 ist dafür nur eine Möglichkeit, wenn `mode` ihn einschaltet (`WIFI_MODE_AP` oder `WIFI_MODE_APSTA`). Bei `WIFI_MODE_STA` wie im Beispiel oben gibt es keinen Access Point.

    Die BOOT-Taste setzt nichts zurück: Die Firmware wertet sie im aktuellen Stand weder beim Start noch im Betrieb aus. Zum Zurücksetzen gibt es zwei Wege (aus dem Code, im Betrieb nicht getestet): Einzelne Dateien über `/delete/<name>` löschen und neu starten, dann gelten für diese Datei die Standardwerte. Oder in der Weboberfläche „Formatieren“ (`/format_file_system/`): Das löscht **alles** in `/data/`, auch `.fboot`, `.libs.json`, `.elf`, `.iop`, Lizenzen und `AuxAssignOfApp.txt`. Danach gelten überall die Standardwerte: beim S3 der Access Point `xx` unter `192.168.4.1`, beim Ethernet DHCP und ohne DHCP-Server eine Link-Local-Adresse.

### Weitere INI-Dateien

**`functionalities.ini`: welche ISOBUS-Clients starten**

    [functionalities]
    PART_6=1
    PART_10=1
    PART_10_TC_LOGIN_DELAY=0

| Schlüssel | Standard | Wirkung |
| --- | --- | --- |
| `PART_6` | `1` | VT-Client (ISO 11783-6) anmelden |
| `PART_6_AUX_INPUT` | `0` | Bei `1` meldet sich der VT-Client als AUX-Input-Gerät statt als normaler VT-Client an |
| `PART_10` | `0` | Task-Controller-Client (ISO 11783-10) anmelden |
| `PART_10_TC_LOGIN_DELAY` | `0` | Verzögerung des TC-Logins (Zahl 0 bis 65535, Einheit nicht geprüft) |
| `PART_13`, `PART_14` | `0` | werden gelesen, aber nirgends ausgewertet, derzeit ohne Wirkung |

`PART_6`, `PART_6_AUX_INPUT` und `PART_10` wirken nur, wenn die Firmware mit der passenden Option gebaut wurde (VT-Client beziehungsweise Task-Controller-Client). Wahrheitswerte als `1` oder `0` schreiben.

**`device.ini`: ISOBUS-NAME**

    [ControlFunction01]
    Function=128
    Function_instance=1
    Identity_number=4711

| Schlüssel | Standard | Bedeutung |
| --- | --- | --- |
| `Selfconfigurable` | `1` | Selbstkonfigurierend |
| `Industry_group` | `2` | Industriegruppe (2 = Landtechnik) |
| `Device_class` | `5` | Geräteklasse |
| `Device_class_instance` | `0` | Instanz der Geräteklasse |
| `Function` | `128` | Funktion |
| `Function_instance` | `0` | Funktionsinstanz |
| `ECU_instance` | `0` | ECU-Instanz |
| `Manufacturer_code` | `1116` | Herstellercode |
| `Identity_number` | `0` | Bei `0` nimmt die Firmware die Seriennummer des Geräts, sonst diesen Wert |

!!! warning "Wertebereiche werden nicht geprüft"
    Die Firmware prüft die Bitbreiten des ISO-Standards nicht (zum Beispiel 3 Bit bei der Industriegruppe, 21 Bit bei der Identity Number). Der Wert geht unverändert ins NAME-Feld. Auf einem Bus müssen die NAMEs aller Geräte verschieden sein. Mit `Identity_number=0` sorgt die Seriennummer dafür. Wer feste Werte einträgt, muss selbst darauf achten.

**`settings.ini`: allgemeine Einstellungen**

    [mDNS]
    Hostname=werkstatt-links

    [SSDP]
    FriendlyName=Werkstatt links

    [CF-A]
    NODE1_SA=128
    bootTimeVT=120

| Abschnitt und Schlüssel | Standard | Bedeutung |
| --- | --- | --- |
| `[mDNS]` `Hostname` | leer (dann `logibus-<MAC>`) | Hostname des Knotens, siehe oben |
| `[SSDP]` `FriendlyName` | `logiBUS Controller` | Name bei der Geräteerkennung im Netz. Vorläufig, der Schlüssel kann sich noch ändern |
| `[CF-A]` `NODE1_SA` | bevorzugte Adresse der Firmware | Bevorzugte ISOBUS-Quelladresse. Die Firmware schreibt den Wert zurück, wenn der Knoten bei der Adressvergabe eine andere Adresse bekommt |
| `[CF-A]` `NODE2_SA` | wie `NODE1_SA` | dasselbe für den zweiten Knoten (ob der Build ihn enthält, nicht geprüft) |
| `[CF-A]` `preferredVT` | `0xFFFFFFFFFFFFFFFF` | NAME des zuletzt benutzten Terminals. Wird von der Firmware geschrieben |
| `[CF-A]` `bootTimeVT` | `120` | Bootzeit des Terminals. Wird von der Firmware geschrieben |
| `[ObjectPool]` `file_de` | `pools/pool_de.iop` | ohne Wirkung: Die Firmware liest den Wert, benutzt ihn aber nicht. Welcher Pool geladen wird, steht unten bei `*.iop`. |
| `[ScalingTest]` | `enable=0` | Test- und Entwicklerschalter, nicht für den Unterricht gedacht |

Zusätzlich lesen und schreiben der 4diac-Funktionsbaustein `INI` und die `INI_A*`-Adapter beliebige Abschnitt/Schlüssel-Paare in der `settings.ini`. Nach jedem Schreiben und Lesen wird gespeichert.

Die Firmware schreibt die `settings.ini` selbst: Jeder Zugriff mit Standardwert trägt einen fehlenden Schlüssel samt Standardwert ein, gespeichert wird beim nächsten Speichervorgang (Adresswechsel, VT-Login, Zugriff des INI-Bausteins). Deshalb entsteht die Datei auch ohne Upload mit der Zeit von selbst.

**`settingsReadOnly.ini`: Werte fest vorgeben**

Gleiche Abschnitte und Schlüssel wie `settings.ini`, aber nur zum Lesen:

    [CF-A]
    NODE1_SA = 128
    bootTimeVT = 90

- Steht ein Schlüssel hier, gilt bei jedem Lesen dieser Wert.
- Schreibversuche auf so einen Schlüssel werden abgelehnt (Log: `write rejected, key is read-only`). Der 4diac-Baustein `INI` meldet dann `Key is read-only`.
- Beim Laden löscht die Firmware dieselben Schlüssel aus der `settings.ini`.
- Die Firmware legt die Datei nie selbst an. Fehlt sie, ist das kein Fehler, dann ist alles beschreibbar.

!!! note "Im Umbau"
    `[mDNS]` `Hostname` und die `hostname`-Schlüssel der Netzwerk-INIs (neuer Hostname-Stand) sowie `[SSDP]` `FriendlyName` werden gerade überarbeitet. Die übrigen Dateien und Schlüssel sind es laut Firmware-Stand nicht.

### Weitere Dateien in `/data/`

Neben den INI-Dateien liegen im Verzeichnis `/data/` weitere Dateien. Die Firmware schreibt davon nur die `settings.ini` und die `AuxAssignOfApp.txt`. Alles andere kommt von außen, per Upload oder über die Deploy- und Preload-Skripte.

| Datei | Inhalt | Woher |
| --- | --- | --- |
| `*.fboot` | Boot-Datei der 4diac-Anwendung | Deploy-Skript oder Upload |
| `*.libs.json` | Manifest der ELF-Bibliotheken. Ohne Manifest werden keine ELF-Bibliotheken geladen. | Deploy- oder Preload-Skript |
| `*.elf` | die ELF-Bibliotheken, vom Manifest referenziert | Deploy- oder Preload-Skript |
| `*.iop` | VT-Objektpool (ISO 11783-6), der Name ist frei | Upload oder Deploy |
| `<Poolname>.vis.json` | Tabelle zur Masken-Sichtbarkeit, liegt mit dem Namen des Pools neben diesem | Upload oder Deploy |
| `*.lic`, `*.key` | Lizenz- und Schlüsseldateien, werden beim Start eingelesen | Upload |
| `*.bin` | Firmware-Images | Upload |
| `AuxAssignOfApp.txt` | bevorzugte AUX-Zuordnung (siehe unten) | die Firmware, am Terminal erzeugt |

Die Firmware schreibt keine Logdateien nach `/data/`. SHA-256-Hashes der Dateien berechnet der Dateiserver nur im Arbeitsspeicher (abrufbar unter `/sha256/<datei>`), es entstehen keine Hash-Dateien.

!!! warning "Bei `.fboot`, `.libs.json` und `.iop` gewinnt die alphabetisch erste Datei"
    Liegen mehrere Dateien mit derselben Endung in `/data/`, benutzt die Firmware nur die alphabetisch erste und warnt im Log. Eine alte Datei mit „kleinerem“ Namen gewinnt dadurch still gegen eine neue. Alte Dateien deshalb löschen (`/delete/<name>`). Das Deploy-Skript räumt alte Boot-Dateien und Manifeste selbst auf.

    Ohne `.iop` sucht die Firmware `/data/DefaultPool.iop` und meldet sie als fehlend (`no object pool *.iop in /data`).

**`AuxAssignOfApp.txt`: bevorzugte AUX-Zuordnung**

Die Datei enthält die „bevorzugte AUX-Zuordnung“ (Preferred Assignment, ISO 11783-6): welche AUX-Funktionen des Objektpools welchem AUX-Eingabegerät (zum Beispiel einem Joystick) zugeordnet sind. Sie hat nichts mit `PART_6_AUX_INPUT` zu tun, also damit, dass der Knoten selbst als AUX-Eingabegerät auftritt. Es gibt sie nur in Builds mit VT-Client.

- **Wer schreibt:** die Firmware. Ordnet man am Terminal zu und markiert die Zuordnung als bevorzugt zu speichern, schreibt die Firmware die gesamte aktuelle Zuordnung neu in die Datei. Es ist nicht vorgesehen, sie hochzuladen.
- **Format:** Text, eine Zeile pro Zuordnung, Zeilenende CRLF. Sechs Felder, durch Leerzeichen getrennt: Herstellercode des Eingabegeräts, ModelIdentificationCode, AUX-Typ, Objekt-ID der AUX-Funktion, Objekt-ID des AUX-Eingangs (alle dezimal) und der 64-Bit-NAME des Eingabegeräts als 16 Hexadezimalzeichen.
- **Fehlt die Datei:** Es gibt keine bevorzugten Zuordnungen, die Zuordnung erfolgt neu am Terminal. Auf der Konsole steht `Error opening AuxAssignOfApp.txt`. Das ist kein Absturz.
- **Zuordnung zurücksetzen:** Datei löschen (`/delete/AuxAssignOfApp.txt`). Danach fehlt die bevorzugte Zuordnung, bis am Terminal neu zugeordnet und als bevorzugt gespeichert wird. Ob dafür ein Neustart nötig ist, wurde nicht geprüft.
- **Ungültige Zeilen** werden nicht gemeldet: Felder werden als Zahlen gelesen, Unsinn ergibt 0.

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
