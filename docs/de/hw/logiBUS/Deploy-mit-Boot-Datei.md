# Deploy mit Boot-Datei: .fboot, Manifest, Upload

Diese Anleitung zeigt den Weg **Boot-Datei → Manifest → Upload** am Beispiel des Trainer-Boards (Workspace `test_AX`). Er ist die Alternative zum Online-Deploy aus [Fehlende ELFs auf das Trainer-Board laden](ELFs-auf-das-Board-laden.md). Hintergrund zu den Skripten steht auf der Seite [Deploy-Skripte und Launches](Deploy-Skripte-und-Launches.md).

## Online-Deploy oder Boot-Datei?

| | Online-Deploy | Boot-Datei-Deploy |
| --- | --- | --- |
| Was kommt aufs Board | Die Anwendung wird in die laufende FORTE-Instanz geladen. Die ELFs der **Grundausstattung** müssen vorher per Preload auf dem Board liegen. | Das `.fboot`, ein Manifest und **genau die ELFs, die das `.fboot` braucht**, auch solche außerhalb der Grundausstattung wie `utils`. |
| Nach einem Neustart | Die Anwendung ist weg. | FORTE lädt das `.fboot` beim Start. Das Board startet auch ohne IDE mit der Anwendung. |
| Typisch für | Schnelles Ausprobieren, Übungen. | Dauerhafte Installation, Betrieb ohne IDE. |
| Knoten | Jedes erreichbare Board (`logibus-<MAC>.local`, bei einem Gerät im Netz auch `logibus.local`, oder IP). | Nur Knoten, die in `deploy_common.py` eingetragen sind (siehe unten). |

## Ablauf

### Schritt 1: Boot-Datei aus der IDE erzeugen

In der 4diac IDE erzeugt die Funktion **Create Forte BootFile** (auch **Create boot-files** genannt) das `.fboot` des Geräts. Pro Gerät entsteht eine Datei `<System>_<Gerät>.fboot`, für das Trainer-Board `test_AX_FORTE_PC_AX.fboot`. Sie gehört nach `Ventilsteuerung/boot-files/`.

**Klickweg in der 4diac IDE 3.4:** Rechtsklick auf die **Resource** oder auf das **Gerät** und **Create Forte BootFile** wählen. Hat das System mehrere Geräte, löst man die Funktion auf dem ersten Gerät aus und wählt die anderen Geräte im Dialog dazu.

!!! warning "Geräteprofil OPC UA"
    Steht das Profil des Geräts auf OPC UA, scheitert **Create Forte BootFile**. Abhilfe: das Profil vorübergehend auf HOLOBLOC umstellen (siehe `OPCUA_Bootfile_Workaround.md` im Trainingsprojekt). Das Gerät `test_AX/FORTE_PC_AX` hat bereits das Profil HOLOBLOC und ist nicht betroffen.

Ändert man später eine `.SUB`, wirkt das erst nach einem **neuen Export** und einem Neustart des Boards.

### Schritt 2: Manifest erzeugen

`make_libs_manifest.py` liest die Typen aus dem `.fboot`, ermittelt daraus die benötigten Bibliotheken samt `requires` aus der `MANIFEST.MF` und schreibt `boot-files/<Boot-Datei>.libs.json`. Das Manifest enthält SHA-256 und Größe des `.fboot` und der benötigten ELFs. Das Skript arbeitet nur lokal, ohne Netzwerkzugriff.

In der IDE: **Run → External Tools → `RunSkript_MakeLibsManifestAX.bat`**. Oder im Ordner `Ventilsteuerung/` auf der Kommandozeile:

    python scripts_central/make_libs_manifest.py

Mit `--out <Pfad>` lässt sich die Ausgabedatei ändern. Eine Knotenwahl gibt es hier nicht.

!!! warning "Nie ein `.fboot` ohne frisch erzeugtes Manifest deployen"
    Stimmen SHA-256 oder Größe der Boot-Datei nicht mit dem Manifest überein, meldet das Gerät `WRONG`. Nach jedem neuen Export deshalb zuerst das Manifest neu erzeugen. Das gilt auch vor dem Einchecken ins Repository.

### Schritt 3: Hochladen

`make_4diac_training1_deploy.py` lädt das `.fboot`, das Manifest und genau die benötigten ELFs per HTTP (`POST /upload/<datei>`) auf das Board, gleicht sie über den Hash ab und startet das Board **nicht** neu. Der Aufruf `RunSkript_DeployAX.bat` führt erst das Manifest-Skript aus und danach das Deploy-Skript. Den genauen Ablauf des Skripts beschreibt der Abschnitt [Ablauf eines Boot-Datei-Deploys](Deploy-Skripte-und-Launches.md#ablauf-eines-boot-datei-deploys).

In der IDE: **Run → External Tools → `RunSkript_DeployAX.bat`**.

Das Skript sucht die Boot-Datei in dieser Reihenfolge:

1. die neueste gestempelte Datei `test_AX_FORTE_PC_AX_*.fboot` in `Ventilsteuerung/`,
2. `Ventilsteuerung/test_AX_FORTE_PC_AX.fboot`,
3. `Ventilsteuerung/boot-files/test_AX_FORTE_PC_AX.fboot`.

Fehlt die Datei, bricht es mit „Fehlende Dateien zuerst neu bauen/exportieren (4diac-IDE-Export)“ ab.

### Schritt 4: Board neu starten

FORTE liest das `.fboot` nur beim Start. Das Board von Hand neu starten, zum Beispiel mit dem **Reboot**-Button der Weboberfläche `http://<ip>/`.

## Welche Knoten kennt das Skript?

Das Deploy-Skript wertet keine Argumente aus. Die Knoten stehen fest in `scripts_central/deploy_common.py`: `NODE_BASES` ordnet jeder Knoten-Adresse ihre Dateien zu, `NODE_ORDER` legt die Reihenfolge fest. Derzeit gibt es dort für `test_AX` nur einen fest eingetragenen Knoten mit `test_AX_FORTE_PC_AX.fboot`. Seine Adresse hängt vom jeweiligen Netz ab (zum Beispiel von der DHCP-Vergabe des Routers) und steht nur im Skript. Für ein beliebiges Trainer-Board unter `logibus.local` geht dieser Weg also nicht ohne Weiteres. Dafür gibt es den Online-Deploy.

Einen neuen Knoten trägt man nach Lesen des Codes so ein (nicht ausprobiert): neuer Eintrag in `NODE_BASES` und `REPO_PATHS` sowie in `NODE_ORDER` (beide in `deploy_common.py`) und `NODE_ARCH` (in `elf_libs_manifest_lib.py`). Die Zuordnung der Dateinamen zu den Pfaden im Repository steht in `REPO_PATHS`, auch die der `.libs.json`.

## Weitere Stolperfallen

- **Veraltetes `.fboot`:** Wirkt eine Änderung nicht, wurde nach der Änderung nicht neu exportiert oder das Board nicht neu gestartet.
- **Konstanten aus GCF-Dateien:** Nach einer Änderung einer `.gcf` von außen kann die IDE Boot-Dateien mit verschobenen Adressen erzeugen (bei OPC UA sogar verschachtelte Adressen). Abhilfe: in der IDE **Refresh**, dann neu erzeugen.
- **Weitere Dateien:** Manche Knoten brauchen zusätzlich einen VT-Objektpool (`.iop` und `.vis.json`), der im Eintrag des Knotens in `NODE_BASES` steht.
