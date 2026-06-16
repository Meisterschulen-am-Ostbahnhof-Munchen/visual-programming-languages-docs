# AI_MUX_3


![AI_MUX_3](./AI_MUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AI_MUX_3** ist ein generischer Analog-Multiplexer, der über drei Adapter-Eingänge (IN1, IN2, IN3) verfügt. Abhängig vom Index K wird einer dieser Eingänge auf den Adapter-Ausgang OUT durchgeschaltet. Der Baustein arbeitet ereignisgesteuert: Ein REQ-Ereignis löst die Auswahl aus und bestätigt mit CNF.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Confirmation of Set Index K |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index |

### **Daten-Ausgänge**
Keine eigenen Datenausgänge – die Ausgangsdaten werden über den Adapter OUT bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug (Ausgang) | OUT | adapter::types::unidirectional::AI | IN1 für K=0, IN2 für K=1, IN3 für K=2 |
| Socket (Eingang) | IN1 | adapter::types::unidirectional::AI | Eingangswert 1 |
| Socket (Eingang) | IN2 | adapter::types::unidirectional::AI | Eingangswert 2 |
| Socket (Eingang) | IN3 | adapter::types::unidirectional::AI | Eingangswert 3 |

## Funktionsweise
Der Baustein wartet auf ein REQ-Ereignis. Sobald es eintrifft, wird der aktuelle Wert des Index K ausgewertet:
- **K = 0** → Der Adapter IN1 wird auf den Ausgang OUT durchgeschaltet.
- **K = 1** → Der Adapter IN2 wird auf den Ausgang OUT durchgeschaltet.
- **K = 2** → Der Adapter IN3 wird auf den Ausgang OUT durchgeschaltet.
- **K > 2** → Es findet keine Durchschaltung statt; der Ausgang OUT bleibt unverändert (undefiniertes Verhalten).

Die Durchschaltung erfolgt über die unidirektionalen Adapterdefinitionen. Die Datenflüsse werden je nach Implementierung der zugrundeliegenden Adapter-Typen ausgetauscht. Nach erfolgreicher Verarbeitung wird das CNF-Ereignis ausgelöst.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle**: Der FB nutzt das 4diac-Adapterkonzept für eine flexible Kopplung analoger Signalquellen und -senken.
- **Generische Ausführung**: Dank des Attributs `GenericClassName = 'GEN_AI_MUX'` kann der Baustein in verschiedenen Kontexten mit verschiedenen Adapterimplementierungen (z. B. unterschiedlichen Wertebereichen oder Einheiten) verwendet werden.
- **Unidirektionale Datentypen**: Sowohl Eingänge als auch Ausgang verwenden unidirektionale Adapter (`unidirectional::AI`), was eine einfache Weiterleitung von Messwerten ohne Rückmeldung ermöglicht.

## Zustandsübersicht
Der Funktionsblock besitzt keinen expliziten Zustandsautomaten. Die Logik beschränkt sich auf eine ereignisgesteuerte Umschaltung, die in einem Single‑Step‑Zyklus abläuft.

## Anwendungsszenarien
- **Messwerterfassung**: Auswahl zwischen drei verschiedenen analogen Sensoren (z. B. Temperatur, Druck, Füllstand) über einen Steuerbefehl.
- **Signalumschaltung**: In einer Steuerung kann der Index K durch eine übergeordnete Logik dynamisch gesetzt werden, um zwischen verschiedenen Signalquellen umzuschalten.
- **Redundanz**: Umschaltung auf einen Ersatzsensor bei Ausfall des primären Sensors.

## Vergleich mit ähnlichen Bausteinen
- **Standard-Multiplexer mit Dateneingängen**: Im Gegensatz zu FB-Typen, die direkte `ANY`-Dateneingänge verwenden, arbeitet `AI_MUX_3` rein adapterbasiert. Dies ermöglicht eine bessere Modularität, da die angehängten Adapter selbst komplexe Datenstrukturen oder Verarbeitungslogik enthalten können.
- **Mehrkanal-Multiplexer**: Ein Baustein mit mehr als drei Kanälen (z. B. AI_MUX_4) würde analog funktionieren, aber durch die Adapterdefinition ist eine Erweiterung durch mehrere Instanzen oder einen eigenen FB mit mehr Sockets möglich.

## Fazit
Der **AI_MUX_3** ist ein kompakter, generischer Analog-Multiplexer für die 4diac-IDE. Durch den Einsatz von Adaptern und die Ereignissteuerung eignet er sich besonders für flexible, modulare Automatisierungslösungen, bei denen mehrere analoge Signalquellen ausgewählt und an einen einzigen Ausgang weitergeleitet werden müssen.