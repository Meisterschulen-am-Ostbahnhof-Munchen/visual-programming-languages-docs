# version

```{index} single: version
```
## 🎧 Podcast

* ["Store Version" – Dein Schlüssel zur Verwaltung von Objektdatenpools im nichtflüchtigen VT-Speicher (ISO 11783-6)](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/Store-Version--Dein-Schlssel-zur-Verwaltung-von-Objektdatenpools-im-nichtflchtigen-VT-Speicher-ISO-11783-6-e36vfh0)
* [VT-Versionen verstehen: Dein Weg zum Meister der Land- und Baumaschinenmechatronik](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/VT-Versionen-verstehen-Dein-Weg-zum-Meister-der-Land--und-Baumaschinenmechatronik-e36a8e8)

## 📺 Video

* ["Store Version" – Dein Schlüssel zur Verwaltung von Objektdatenpools im nichtflüchtigen VT-Speich...](https://www.youtube.com/watch?v=eVseHOOO9qM)

## Einleitung
Der Funktionsblock `version` dient der einfachen Weitergabe einer Versionsinformation. Er empfängt eine Zeichenkette (String) als Eingabe und gibt diese unverändert an seinem Ausgang wieder. Dieser Baustein ist nützlich, um Versionsnummern oder andere Kennzeichnungen innerhalb einer Anwendungskette zu transportieren oder für Diagnosezwecke bereitzustellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Dieses Ereignis löst die Verarbeitung des Funktionsblocks aus. Bei seinem Eintreffen wird der Wert des zugehörigen Dateneingangs `VERSION` an den Datenausgang `VERSIONO` kopiert.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses Ereignis signalisiert die erfolgreiche Beendigung der Operation. Es wird gleichzeitig mit der Datenausgabe `VERSIONO` erzeugt.

### **Daten-Eingänge**
*   **VERSION** (STRING): Dieser Eingang erwartet die Zeichenkette, die weitergegeben werden soll (z.B. eine Versionsnummer wie "1.2.3").

### **Daten-Ausgänge**
*   **VERSIONO** (STRING): Dieser Ausgang gibt den empfangenen Wert von `VERSION` unverändert aus.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Die Funktionsweise des `version`-Blocks ist äußerst einfach und deterministisch. Bei jedem Eintreffen des Ereignisses `REQ` wird der aktuelle Wert der Eingangsvariablen `VERSION` in die Ausgangsvariable `VERSIONO` kopiert. Unmittelbar nach dieser Zuweisung wird das Bestätigungsereignis `CNF` zusammen mit dem neuen Ausgabewert erzeugt. Es findet keine Formatprüfung, Manipulation oder Speicherung des Wertes statt.

## Technische Besonderheiten
*   **Einfache Durchreichung**: Der Block führt keine Transformation oder Logik auf den Daten durch.
*   **Direkte Kopplung**: Die Ereignisse `REQ` und `CNF` sind direkt gekoppelt; die Ausführungszeit ist vernachlässigbar.
*   **Kein interner Zustand**: Der Block besitzt keinen eigenen Speicher. Jede Ausführung ist ausschließlich von den aktuellen Eingängen abhängig.

## Zustandsübersicht
Der Funktionsblock `version` ist zustandslos. Er verharrt in einem einzigen, passiven Zustand, bis ein `REQ`-Ereignis eintrifft. Die Reaktion darauf (Kopieren der Daten und Auslösen von `CNF`) ist instantan und führt nicht zu einem anderen Zustand.

## Anwendungsszenarien
1.  **Versionsweitergabe**: In einer Anwendungskette kann ein übergeordneter Baustein (z.B. ein Master- oder Verwaltungs-FB) seine eigene Version an diesen Block übergeben, um sie an nachgelagerte Diagnose- oder Logging-Funktionen zu senden.
2.  **Diagnose und Tracing**: Der Block kann verwendet werden, um bestimmte Software-Stände oder Konfigurationsversionen in einem zentralen Log- oder Anzeigesystem zu sammeln.
3.  **Datenkonsolidierung**: In Verbindung mit anderen Funktionsblöcken kann er dazu dienen, Versionsinformationen aus verschiedenen Quellen an einer zentralen Stelle (z.B. einem HMI oder einem Netzwerkdienst) bereitzustellen.

## Vergleich mit ähnlichen Bausteinen
*   **`E_SR` oder `E_RS` (Flip-Flops)**: Diese Blöcke besitzen einen internen Zustand (gesetzt/rückgesetzt), der durch Ereignisse geändert wird. Der `version`-Block hat keinen solchen Zustand.
*   **`E_MERGE`**: Dieser Block fusioniert Ereignisse von mehreren Eingängen. Der `version`-Block hat nur einen einzigen Ereigniseingang und verarbeitet keine Ereignisströme.
*   **Einfache Daten-Blöcke (z.B. `E_R_TRIG`)**: Diese reagieren auf Signalflanken oder führen Timing-Operationen durch. Der `version`-Block führt ausschließlich eine Datenkopie durch.
*   **Generische Blöcke wie `COPY`**: Ein `COPY`-Block würde eine ähnliche Funktion erfüllen (Daten von A nach B kopieren), ist aber typischerweise ein reiner Datenbaustein ohne Ereignissteuerung. Der `version`-Block folgt dem standardmäßigen IEC 61499-Ereignis-/Datenfluss-Paradigma.

## Fazit
Der `version`-Funktionsblock ist ein minimalistisches und spezialisiertes Werkzeug zur Weitergabe von String-Informationen innerhalb eines ereignisgesteuerten Steuerungssystems. Seine Stärke liegt in der Einfachheit und Klarheit seines Zwecks. Für reine Datenkopien ohne Ereignislogik könnten alternative Implementierungen in Frage kommen, für die Integration in eine standardkonforme IEC 61499-Applikation mit klar definiertem Ereignisfluss ist er jedoch gut geeignet.