# BOOL_TO_QUARTER

![BOOL_TO_QUARTER](https://github.com/user-attachments/assets/873eaa98-890d-46c7-b17f-5f1ae91aa3d4)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BOOL_TO_QUARTER` dient zur Umwandlung eines booleschen Eingangssignals in einen 2-Bit-Ausgang (Quarter Byte) mit zwei definierten Zuständen. Der Block ist besonders nützlich in Steuerungssystemen, wo boolesche Signale in spezifische Steuerbefehle umgewandelt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Ein Ereignis, das die Umwandlung auslöst. Wird mit dem Daten-Eingang `I` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die Ausführung der Umwandlung. Wird mit dem Daten-Ausgang `QB` verknüpft.

### **Daten-Eingänge**
- **I**: Boolescher Eingang (`BOOL`), der den Zustand für die Umwandlung liefert. Initialwert: `BOOL#FALSE`.

### **Daten-Ausgänge**
- **QB**: Ausgang vom Typ `BYTE`, der als 2-Bit-Wert (Quarter Byte) ausgegeben wird. Initialwert: `quarter::COMMAND_DISABLE`.  
  Mögliche Zustände:
  - `quarter::COMMAND_ENABLE` (wenn `I` = `TRUE`)
  - `quarter::COMMAND_DISABLE` (wenn `I` = `FALSE`)

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock überprüft den Zustand des booleschen Eingangs `I`:
- Ist `I` `TRUE`, wird der Ausgang `QB` auf `quarter::COMMAND_ENABLE` gesetzt.
- Ist `I` `FALSE`, wird `QB` auf `quarter::COMMAND_DISABLE` gesetzt.  
Die Umwandlung wird durch das Ereignis `REQ` ausgelöst, und die Bestätigung erfolgt über `CNF`.

## Technische Besonderheiten
- Der Ausgang `QB` nutzt nur 2 Bit eines Bytes, was eine effiziente Speichernutzung ermöglicht.
- Initialwerte sind vordefiniert, um unerwartetes Verhalten zu vermeiden.

## Zustandsübersicht
| Eingang `I` | Ausgang `QB`               |
|-------------|----------------------------|
| `TRUE`      | `quarter::COMMAND_ENABLE`  |
| `FALSE`     | `quarter::COMMAND_DISABLE` |

## Anwendungsszenarien
- Steuerung von Aktoren, die spezifische 2-Bit-Befehle erwarten (z. B. Ein/Aus-Schaltungen mit erweiterten Zuständen).
- Signalumwandlung in Protokollen, die Quarter-Byte-Kommandos verwenden.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu einfachen `BOOL_TO_BYTE`-Blöcken bietet `BOOL_TO_QUARTER` eine spezialisierte Umwandlung mit klar definierten Zuständen (`COMMAND_ENABLE`/`COMMAND_DISABLE`).
- Ideal für Systeme, die nur zwei Zustände benötigen, aber in einem Byte-Format kommunizieren.

## Fazit
Der `BOOL_TO_QUARTER`-Block ist ein effizientes Werkzeug zur Umwandlung boolescher Signale in Quarter-Byte-Kommandos. Seine klare Zustandslogik und einfache Integration machen ihn besonders für Steuerungsanwendungen geeignet.
