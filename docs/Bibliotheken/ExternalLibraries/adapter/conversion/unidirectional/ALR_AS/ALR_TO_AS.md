# ALR_TO_AS


![ALR_TO_AS](./ALR_TO_AS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ALR_TO_AS** ist ein zusammengesetzter (Composite) Baustein, der einen **LREAL-Adapter** (ALR) in einen **SINT-Adapter** (AS) umwandelt. Er kapselt die Konvertierung eines Gleitkommawertes (LREAL) in einen vorzeichenbehafteten 8‑Bit‑Ganzzahlwert (SINT) und stellt die Ergebnisdaten über den SINT‑Adapter bereit. Der Baustein wird typischerweise in der Automatisierungstechnik eingesetzt, wenn Daten zwischen unterschiedlichen Adapter‑Schnittstellen vermittelt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine separaten Ereignis-Eingänge. Die Steuerung der Konvertierung erfolgt über das Ereignis des angeschlossenen **ALR‑Adapter‑Sockets** (`ALR_IN.E1`).

### **Ereignis-Ausgänge**

Der Baustein besitzt keine separaten Ereignis-Ausgänge. Der Abschluss der Konvertierung wird über das Ereignis des **AS‑Adapter‑Plugs** (`AS_OUT.E1`) signalisiert.

### **Daten-Eingänge**

Der Baustein besitzt keine separaten Daten-Eingänge. Die Eingangsdaten (LREAL‑Wert) werden über den **ALR‑Adapter** (`ALR_IN.D1`) bereitgestellt.

### **Daten-Ausgänge**

Der Baustein besitzt keine separaten Daten-Ausgänge. Die Ausgangsdaten (SINT‑Wert) werden über den **AS‑Adapter** (`AS_OUT.D1`) zur Verfügung gestellt.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `ALR_IN` | Socket | `adapter::types::unidirectional::ALR` | LREAL‑Adapter‑Eingang: liefert den zu konvertierenden LREAL‑Wert sowie ein Auslöseereignis (`E1`). |
| `AS_OUT` | Plug | `adapter::types::unidirectional::AS` | SINT‑Adapter‑Ausgang: stellt den konvertierten SINT‑Wert sowie ein Bestätigungsereignis (`E1`) bereit. |

## Funktionsweise

Der Baustein ist als Composite FB realisiert. Er enthält intern einen Funktionsblock `F_LREAL_TO_SINT` aus der IEC 61131‑Bibliothek. Die Verbindungen innerhalb des Netzwerks bewirken:

1. **Ereignisgesteuerte Aktivierung**: Ein eingehendes Ereignis am Adapter `ALR_IN` (`E1`) triggert den Konvertierungs‑FB (`Convert.REQ`).
2. **Datenkonvertierung**: Der LREAL‑Wert von `ALR_IN.D1` wird an den Eingang `Convert.IN` weitergeleitet. Der FB wandelt diesen Wert in einen SINT‑Wert um (Rundung gemäß IEC 61131‑Regeln).
3. **Ergebnisausgabe**: Nach erfolgreicher Konvertierung signalisiert `Convert.CNF` ein Ereignis an den Ausgangsadapter `AS_OUT` (`E1`), und der konvertierte SINT‑Wert wird an `AS_OUT.D1` übergeben.

Damit wird eine synchrone, ereignisgesteuerte Umwandlung eines LREAL‑Werts in einen SINT‑Wert über Adapter‑Schnittstellen ermöglicht.

## Technische Besonderheiten

- **Composite‑Struktur**: Der Baustein kapselt die Konvertierungslogik vollständig in einem Netzwerk, sodass die Implementierung transparent und leicht erweiterbar ist.
- **Adapter‑basiert**: Statt einzelner Ereignis‑ und Datenports werden standardisierte uni‑direktionale Adapter (`ALR` und `AS`) verwendet. Dies vereinfacht die Integration in bestehende Adapter‑basierten Architekturen.
- **Wiederverwendung**: Der interne FB `F_LREAL_TO_SINT` ist ein bewährter IEC‑Baustein und stellt die korrekte Konvertierung nach Norm sicher.
- **Keine eigene Zustandsmaschine**: Da es sich um einen Composite FB handelt, existiert kein eigenständiger Zustandsautomat; die Steuerung erfolgt allein durch die verbundenen Adapter‑Ereignisse.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Sein Verhalten wird durch den internen FB `F_LREAL_TO_SINT` und die Ereignisverbindungen bestimmt. Dieser interne FB durchläuft einen einfachen **IDLE → CONVERTING → DONE**‑Zyklus, der über die Ereignisse `REQ` und `CNF` gesteuert wird. Für den Anwender ist der Baustein daher transparent als **ereignisgesteuerter Konverter** nutzbar.

## Anwendungsszenarien

- **Datenbrücke zwischen Systemen**: Wenn ein Steuerungsteil LREAL‑Werte über einen `ALR`‑Adapter liefert, ein nachgeschaltetes Modul aber SINT‑Werte über einen `AS`‑Adapter erwartet.
- **Einheitliche Adapter‑Schnittstellen**: Vereinfachung des Systemdesigns, indem Konvertierungen in eigenständige Bausteine ausgelagert werden.
- **SPS‑Anbindung**: Ankopplung von Sensoren oder Aktoren, die mit LREAL‑Genauigkeit rechnen, an eine SINT‑basierte Buskommunikation.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einer direkten Verdrahtung eines `F_LREAL_TO_SINT`‑Bausteins mit einzelnen Ereignis‑/Datenports bietet der `ALR_TO_AS`‑Baustein eine **höhere Abstraktion durch Adapter**. Dies erleichtert den Austausch von Daten zwischen Komponenten, die bereits auf Adapter‑Schnittstellen ausgelegt sind. Ein ähnlicher Baustein könnte `ALR_TO_ADI` (Umwandlung nach INT) oder `ALR_TO_UDI` (Umwandlung nach UDINT) sein, welche analog aufgebaut sind, aber andere Zieldatentypen verwenden.

## Fazit

Der `ALR_TO_AS`‑Funktionsblock ist eine saubere, adapterbasierte Lösung zur Umwandlung von LREAL‑ in SINT‑Werte in der 4diac‑IDE. Durch die Composite‑Struktur und die Verwendung standardisierter IEC‑Konvertierungsbausteine gewährleistet er eine zuverlässige, ereignisgesteuerte Datenkonvertierung und erleichtert die Integration in modulare Automatisierungssysteme.