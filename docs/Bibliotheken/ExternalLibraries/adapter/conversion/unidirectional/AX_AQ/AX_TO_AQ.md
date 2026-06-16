# AX_TO_AQ


![AX_TO_AQ](./AX_TO_AQ.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AX_TO_AQ** dient der Umwandlung eines booleschen Signals (AX‑Adapter) in ein Quarter‑Byte‑Signal (AQ‑Adapter). Die Umwandlung erfolgt auf Basis einer ereignisgesteuerten COMMAND‑Logik, bei der ein eingehendes Ereignis die Konvertierung auslöst und das Ergebnis über ein Ausgangsereignis quittiert wird. Der Baustein kapselt die Konvertierungslogik in einem internen Sub‑Funktionsblock und ermöglicht so eine saubere Trennung zwischen Adaptertypen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `IN.E1`  | Startet die Konvertierung des eingehenden Bool‑Werts. Wird als Befehl (COMMAND) interpretiert. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `OUT.E1` | Bestätigt die abgeschlossene Konvertierung und signalisiert die Gültigkeit des Ausgangs‑Quarter‑Byte‑Werts. |

### **Daten-Eingänge**

| Daten | Typ | Beschreibung |
|-------|-----|--------------|
| `IN.D1` | BOOL (über AX‑Adapter) | Boolescher Eingangswert, der in ein Quarter‑Byte umgewandelt werden soll. |

### **Daten-Ausgänge**

| Daten | Typ | Beschreibung |
|-------|-----|--------------|
| `OUT.D1` | Quarter Byte (über AQ‑Adapter) | Ausgangswert – das umgewandelte Quarter‑Byte (4‑Bit‑Darstellung). |

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `IN`    | Socket   | `adapter::types::unidirectional::AX` | Empfängt das boolesche Signal. Der AX‑Adapter stellt einen unidirektionalen Bool‑Kanal bereit. |
| `OUT`   | Plug     | `adapter::types::unidirectional::AQ` | Stellt das konvertierte Quarter‑Byte‑Signal bereit. Der AQ‑Adapter ist ein unidirektionaler Quarter‑Byte‑Kanal. |

## Funktionsweise
1. Ein Ereignis an `IN.E1` triggert die interne Verarbeitung.
2. Der Sub‑Funktionsblock `BOOL_TO_QUARTER` wird über seinen Ereigniseingang `REQ` aktiviert und wandelt den an `I` anliegenden Bool‑Wert in ein Quarter‑Byte um.
3. Nach Abschluss der Konvertierung meldet `BOOL_TO_QUARTER` dies über sein Ereignis `CNF`, das an `OUT.E1` durchgereicht wird.
4. Gleichzeitig wird der konvertierte Wert über die Datenverbindung vom Ausgang `QB` des Sub‑Blocks an `OUT.D1` übergeben.

Der gesamte Prozess ist ereignisgesteuert und erfolgt ohne interne Zustandsspeicherung – jeder Befehl erzeugt eine vollständige Umwandlung.

## Technische Besonderheiten
- **Interne Kapselung**: Die Konvertierungslogik wird vollständig durch den eingebetteten Funktionsblock `logiBUS::utils::quarter::BOOL_TO_QUARTER` realisiert. Dies vereinfacht Wartung und Austausch der Konvertierungsimplementierung.
- **Unidirektionalität**: Sowohl Eingangs‑ als auch Ausgangsadapter sind unidirektional ausgelegt; eine Rückkopplung oder bidirektionale Nutzung ist nicht vorgesehen.
- **Ereignissynchronisation**: Der Ausgangs‑Ereignispuls `OUT.E1` garantiert, dass die Daten am Ausgang `OUT.D1` gültig sind, bevor der aufrufende Baustein weiterarbeitet.
- **Lizenz und Herkunft**: Der Baustein ist unter der EPL‑2.0 lizenziert und im Paket `adapter::conversion::unidirectional` eingeordnet (siehe CompilerInfo).

## Zustandsübersicht
Der Funktionsblock besitzt keine explizite Zustandsmaschine. Er arbeitet als reine Kombinationslogik mit ereignisgesteuerter Auslösung:
- **Ruhezustand**: Es liegt kein Ereignis an `IN.E1` an. Ausgänge bleiben unverändert.
- **Aktiv**: Ein Ereignis an `IN.E1` startet die Umwandlung. Nach Abschluss wird `OUT.E1` ausgelöst und der neue Wert an `OUT.D1` ausgegeben. Danach kehrt der Baustein in den Ruhezustand zurück.

## Anwendungsszenarien
- **Übersetzung von Bussignalen**: In einem industriellen Bussystem werden boolesche Steuersignale (z. B. Bit‑Werte von Sensoren) in kompakte 4‑Bit‑Datenwörter umgewandelt, um die Bandbreite zu reduzieren.
- **Bit‑zu‑Quarter‑Byte‑Wandler in Automatisierungsnetzwerken**: Wenn ein Subsystem nur Quarter‑Byte‑Werte verarbeiten kann, aber boolesche Eingänge anliegen.
- **Adapterbrücke**: Der Baustein fungiert als Zwischenstück zwischen einem AX‑kompatiblen Sender und einem AQ‑kompatiblen Empfänger in einer unidirektionalen Kette.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Aufgabe | Unterschied |
|----------|---------|-------------|
| `BOOL_TO_BYTE` | Konvertiert BOOL in ein Byte (8‑Bit) | Arbeitet mit 8‑Bit‑ statt 4‑Bit‑Ausgabe. Benötigt andere Adaptertypen (z. B. `AB`). |
| `BOOL_TO_WORD` | Konvertiert BOOL in ein Word (16‑Bit) | Liefert eine breitere Ausgabe, oft für analoge oder digitale Wort‑Signale. |
| `AX_TO_AQ` | Konvertiert BOOL (AX) in Quarter Byte (AQ) | Speziell auf die unidirektionale Adapterkombination AX↔AQ zugeschnitten und erzeugt nur 4‑Bit‑Werte. |

## Fazit
Der **AX_TO_AQ**‑Funktionsblock ist ein spezialisierter und schlanker Konverter für die Umwandlung boolescher Adaptersignale in das Quarter‑Byte‑Format. Durch die klare ereignisgesteuerte Struktur und die interne Wiederverwendung eines standardisierten Umwandlungsbausteins eignet er sich ideal für den Einsatz in Automatisierungs‑ und Bussystemen, in denen eine platzsparende Übermittlung boolescher Zustände erforderlich ist. Die einfache Schnittstelle und die Unidirektionalität erleichtern die Integration in bestehende Kommunikationsabläufe.