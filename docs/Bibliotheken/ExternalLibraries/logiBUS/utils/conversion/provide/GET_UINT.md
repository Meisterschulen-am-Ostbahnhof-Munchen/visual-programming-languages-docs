# GET_UINT


![GET_UINT](./GET_UINT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **GET_UINT** liest den aktuellen Wert einer als InOut-Variable übergebenen `UINT`-Quelle aus und stellt diesen als gepufferten Ausgangswert bereit. Er dient dazu, einen konsistenten Schnappschuss eines externen oder internen UINT-Werts zu einem definierten Zeitpunkt zu erfassen und für die weitere Verarbeitung im Ablauf bereitzustellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **REQ**  | Normaler Ausführungsauftrag; löst das Lesen der InOut-Variablen und die Aktualisierung des Ausgangs aus. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **CNF**  | Bestätigt die erfolgreiche Ausführung von REQ und signalisiert, dass die Ausgänge gültig sind. |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| **IN**   | UINT  | Quellvariable, die als InOut-Parameter bereitgestellt wird. Der Wert wird bei REQ ausgelesen und unverändert an den Ausgang übergeben. Standardwert: `0`. |

**Hinweis:** `IN` ist als InOut-Variable deklariert, wird innerhalb des Bausteins jedoch nur lesend verwendet.

### **Daten-Ausgänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| **OUT**  | UINT  | Gepufferter Ausgangswert, der den bei der letzten REQ-Ausführung gelesenen Wert von `IN` enthält. Standardwert: `0`. |

### **Adapter**

Keine.

## Funktionsweise

Der Baustein verfügt über einen einzigen Ausführungszustand (`REQ`). Wird der Ereigniseingang `REQ` aktiviert, führt er folgende Aktion aus:

1. **Lesen** des aktuellen Werts der InOut-Variablen `IN`.
2. **Kopieren** dieses Werts in die Ausgangsvariable `OUT`.
3. **Auslösen** des Ereignisausgangs `CNF`, um die Fertigstellung zu signalisieren.

Die Verarbeitung erfolgt strikt sequenziell und ohne Verzögerung.

## Technische Besonderheiten

- **InOut-Variable als Quelle:** Obwohl `IN` als InOut deklariert ist, wird sie ausschließlich lesend verwendet. Der Baustein schreibt nicht zurück, sodass die Quelle unverändert bleibt.
- **Pufferung:** Der Ausgang `OUT` hält den Wert, bis der nächste `REQ` ausgeführt wird. Dadurch wird eine Entkopplung zwischen der Quelle und der nachfolgenden Logik erreicht.
- **Einfaches Zustandsmodell:** Der Baustein besteht nur aus einem Zustand, sodass keine komplexen Ablaufsteuerungen erforderlich sind.

## Zustandsübersicht

| Zustand | Beschreibung |
|---------|--------------|
| **REQ** | Wartet auf das Eintreffen des Ereignisses `REQ` und führt dann die Zuweisung `OUT := IN` durch. Anschließend wird `CNF` gesendet. |

Es gibt keinen expliziten Start- oder Endzustand; nach der Ausführung bleibt der Baustein im Zustand `REQ` bereit für den nächsten Auftrag.

## Anwendungsszenarien

- **Sichere Wertübernahme:** Ein UINT-Wert aus einer globalen Variablen oder einem anderen Baustein soll zu einem definierten Zeitpunkt eingefroren werden, um während eines Ablaufs konsistent zu bleiben.
- **Abtastung von Messwerten:** In einer zyklischen Steuerung wird der aktuelle Wert eines Zählers oder Sensors ausgelesen und zwischengespeichert.
- **Datenübergabe zwischen Tasks:** Der Baustein kann als einfache Pufferschicht zwischen asynchronen Kommunikationspfaden dienen.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu einem reinen Eingangsbaustein, der einen festen Datenport verwendet, erlaubt **GET_UINT** die Nutzung einer **InOut-Variablen** als Quelle. Dadurch kann die Variable sowohl von außen beschrieben als auch gelesen werden, ohne eine separate Verbindung zu einem Eingang zu benötigen. Reine Lesebausteine (z. B. UINT-Eingang) bieten keine solcher Flexibilität, sind aber klarer in der Schnittstelle. Gegenüber einem Speicherbaustein (z. B. `R_TRIG` oder `SR`) speichert **GET_UINT** keine Zustände, sondern lediglich den letzten gelesenen Wert.

## Fazit

**GET_UINT** ist ein einfacher, aber nützlicher Funktionsblock, der einen UINT-Wert aus einer InOut-Variablen puffert. Sein minimalistisches Design – ein Ereignis, eine Aktion – macht ihn ideal für Situationen, in denen eine saubere, zeitlich definierte Wertübernahme erforderlich ist. Er eignet sich besonders für Anwendungen, die eine konsistente Datenbasis innerhalb eines Ablaufs benötigen, ohne die Quelle zu beeinflussen.