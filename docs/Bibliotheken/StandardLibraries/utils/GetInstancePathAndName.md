# GetInstancePathAndName

```{index} single: GetInstancePathAndName
```

![GetInstancePathAndName](https://github.com/user-attachments/assets/818b4609-9a6a-4ec7-b8d8-dfd54f003751)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `GetInstancePathAndName` dient dazu, den Instanzpfad und den Instanznamen aus der Laufzeitumgebung abzurufen. Dies ist besonders nützlich für Debugging-Zwecke oder für dynamische Konfigurationen, bei denen der genaue Pfad einer Instanz benötigt wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage, die den Abruf des Instanzpfades und -namens auslöst. Wird mit dem Separatorzeichen `Sep` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Service-Anfrage. Wird mit den Ausgabevariablen `Path` (Instanzpfad) und `Name` (Instanzname) verknüpft.

### **Daten-Eingänge**
- **Sep** (CHAR): Separatorzeichen für den generierten Ausgabepfad. Standardwert ist `'/'`.

### **Daten-Ausgänge**
- **Path** (STRING): Der Instanzpfad des Funktionsblocks.
- **Name** (STRING): Der Instanzname des Funktionsblocks.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Bei Empfang eines `REQ`-Ereignisses wird der Funktionsblock aktiviert.
2. Der Funktionsblock ermittelt den aktuellen Instanzpfad und den Instanznamen aus der Laufzeitumgebung.
3. Der Instanzpfad wird mit dem angegebenen Separatorzeichen `Sep` formatiert.
4. Das `CNF`-Ereignis wird ausgelöst und die ermittelten Werte für `Path` und `Name` ausgegeben.

## Technische Besonderheiten
- Der Standard-Separator für den Pfad ist `'/'`, kann jedoch über den Eingang `Sep` angepasst werden.
- Die Ausgabevariablen `Path` und `Name` sind vom Typ `STRING` und enthalten den vollständigen Pfad bzw. den Namen der Instanz.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Er reagiert ausschließlich auf das `REQ`-Ereignis und gibt sofort die entsprechenden Daten aus.

## Anwendungsszenarien
- **Debugging**: Ermittlung des genauen Pfades einer Instanz zur Fehlersuche.
- **Dynamische Konfiguration**: Verwendung des Instanzpfades für dynamische Konfigurationen oder Logging.
- **Systemüberwachung**: Überwachung und Protokollierung von Instanzpfaden in komplexen Systemen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Funktionsblöcken, die ähnliche Informationen liefern, bietet `GetInstancePathAndName` die Flexibilität, den Separator für den Pfad anzupassen.
- Andere Bausteine könnten nur den Pfad oder nur den Namen liefern, während dieser Funktionsblock beides kombiniert.

## Fazit
Der `GetInstancePathAndName`-Funktionsblock ist ein einfaches, aber mächtiges Werkzeug, um Instanzinformationen aus der Laufzeitumgebung abzurufen. Seine Flexibilität und Einfachheit machen ihn ideal für Debugging und dynamische Konfigurationen.
