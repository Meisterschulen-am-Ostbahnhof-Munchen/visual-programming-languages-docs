# F_UINT_TO_LINT

<img width="1436" height="216" alt="F_UINT_TO_LINT" src="https://github.com/user-attachments/assets/8f25baa4-d194-4dfd-887d-b962e086c413" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_LINT` dient der Konvertierung eines vorzeichenlosen 16-Bit-Integer-Werts (UINT) in einen vorzeichenbehafteten 64-Bit-Integer-Wert (LINT). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen mit unterschiedlicher Wortbreite ausgetauscht oder verarbeitet werden müssen.

* * * * * * * * * *
## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `UINT`, der in einen `LINT`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Ausgangswert vom Typ `LINT`.

### **Adapter**
- Es sind keine Adapter vorhanden.

* * * * * * * * * *
## Funktionsweise
Der Funktionsblock führt eine direkte Zuweisung des Eingangswerts `IN` zum Ausgang `OUT` durch. Da `LINT` einen größeren Wertebereich als `UINT` besitzt, ist die Konvertierung verlustfrei. Der Block wird durch das Ereignis `REQ` aktiviert und signalisiert den Abschluss der Operation mit dem Ereignis `CNF`.

* * * * * * * * * *
## Technische Besonderheiten
- **Verlustfreie Konvertierung**: Da `LINT` (64 Bit) einen größeren Wertebereich als `UINT` (16 Bit) abdeckt, geht bei der Konvertierung keine Information verloren.
- **Einfache Implementierung**: Der Block verwendet einen einfachen Algorithmus zur direkten Zuweisung der Werte.

* * * * * * * * * *
## Zustandsübersicht
1. **Idle-Zustand**: Der Block wartet auf das Ereignis `REQ`.
2. **Aktivierungszustand**: Bei Empfang von `REQ` wird der Eingangswert `IN` gelesen und konvertiert.
3. **Bestätigungszustand**: Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst und der Block kehrt in den Idle-Zustand zurück.

* * * * * * * * * *
## Anwendungsszenarien
- **Datenkonvertierung**: In Systemen, die sowohl 16-Bit- als auch 64-Bit-Daten verarbeiten müssen.
- **Schnittstellenanpassung**: Bei der Kommunikation zwischen Geräten mit unterschiedlicher Wortbreite.
- **Datenverarbeitung**: In Algorithmen, die höhere Präzision für Berechnungen benötigen.

* * * * * * * * * *
## Vergleich mit ähnlichen Bausteinen
- **F_UINT_TO_INT**: Konvertiert `UINT` zu `INT` (16 Bit), aber mit Vorzeichenbehaftung.
- **F_UINT_TO_DINT**: Konvertiert `UINT` zu `DINT` (32 Bit), bietet mehr Wertebereich als `INT`, aber weniger als `LINT`.
- **F_UINT_TO_ULINT**: Konvertiert `UINT` zu `ULINT` (64 Bit), bleibt vorzeichenlos.

* * * * * * * * * *
## Fazit
Der `F_UINT_TO_LINT`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von 16-Bit- vorzeichenlosen Integer-Werten in 64-Bit- vorzeichenbehaftete Integer-Werte. Seine verlustfreie Konvertierung und einfache Handhabung machen ihn ideal für Anwendungen, die eine höhere Präzision oder Kompatibilität mit 64-Bit-Systemen erfordern.
