# AR_MUX_3


![AR_MUX_3](./AR_MUX_3.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock `AR_MUX_3` ist ein generischer 3-fach-Multiplexer für den Adapter-Typ `adapter::types::unidirectional::AR`. Er wählt basierend auf einem Index `K` einen von drei Eingängen (IN1, IN2, IN3) aus und leitet dessen Signal an den Ausgang OUT weiter. Der Baustein wird über ein Ereignis gesteuert und eignet sich zur dynamischen Umschaltung von Datenquellen in IEC 61499-basierten Steuerungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K – löst die Auswahl aus |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung der erfolgten Umschaltung |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index für die Auswahl (0, 1 oder 2) |

### **Daten-Ausgänge**
Keine (die Ausgangsdaten werden über den Adapter OUT bereitgestellt).

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug     | OUT  | adapter::types::unidirectional::AR | Ausgang, der den gewählten Eingang weitergibt |
| Socket   | IN1  | adapter::types::unidirectional::AR | Eingang 1 für Index K = 0 |
| Socket   | IN2  | adapter::types::unidirectional::AR | Eingang 2 für Index K = 1 |
| Socket   | IN3  | adapter::types::unidirectional::AR | Eingang 3 für Index K = 2 |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
1. Ein eingehendes Ereignis am Eingang `REQ` triggert die Verarbeitung.
2. Der aktuelle Wert des Index `K` wird ausgelesen.
3. Abhängig von `K` wird der entsprechende Eingang (IN1, IN2, IN3) auf den Adapter-Ausgang `OUT` durchgeschaltet.
   - Gültige Werte: 0 → IN1, 1 → IN2, 2 → IN3.
   - Werte außerhalb dieses Bereichs führen zu undefiniertem Verhalten (keine explizite Fehlerbehandlung).
4. Nach erfolgreicher Umschaltung wird das Bestätigungsereignis `CNF` gesendet.

Die Adapter sind unidirektional ausgelegt; die Daten fließen vom gewählten Socket zum Plug.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AR_MUX`) deklariert und kann für beliebige `AR`-Adapter verwendet werden.
- **Adapterbasierte Datenübertragung**: Alle Ein- und Ausgänge nutzen Adapter des Typs `adapter::types::unidirectional::AR`, was eine flexible Kopplung mit anderen Bausteinen ermöglicht.
- **Fest definierte Anzahl von 3 Eingängen**: Der Baustein ist nicht parametrisierbar; es gibt keine Möglichkeit, die Anzahl der Eingänge zur Laufzeit zu ändern.
- **Keine Plausibilitätsprüfung**: Der Index `K` wird nicht auf gültige Werte überprüft. Ungültige Indizes (z. B. > 2) können zu unerwartetem Verhalten führen.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten, da die Logik rein durch das Ereignis `REQ` gesteuert wird. Dennoch lässt sich der Ablauf als einfacher Zustandsautomat beschreiben:

| Zustand | Beschreibung |
|---------|-------------|
| IDLE    | Warten auf ein `REQ`-Ereignis |
| SELECT  | Auswahl des Eingangs gemäß Index `K` |
| DONE    | Ausgabe geschaltet, Senden von `CNF`, Rückkehr zu IDLE |

## Anwendungsszenarien
- **Signalumschaltung**: Wechsel zwischen verschiedenen Sensorwerten oder Regelparametern in einer Automatisierungsanwendung.
- **Betriebsartenwahl**: Auswahl unterschiedlicher Steuerungsmodi, z. B. Hand-/Automatikbetrieb, abhängig von einer Benutzereingabe.
- **Test- und Diagnosefunktionen**: Einspielen von Testsignalen auf einen gemeinsamen Ausgangskanal.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Eingänge | Besonderheit |
|----------|-----------------|--------------|
| AR_MUX_2 | 2               | Einfacherer Multiplexer für zwei Quellen |
| AR_MUX_3 | 3               | Vorliegender Baustein |
| AR_MUX_4 | 4               | Erweiterte Variante mit vier Eingängen |

Alle Multiplexer folgen dem gleichen Prinzip und unterscheiden sich nur in der Anzahl der Adapter-Sockets.

## Fazit
Der `AR_MUX_3` ist ein kompakter und funktionaler Funktionsblock zur Auswahl eines von drei Adapter-Signalen. Er eignet sich besonders für Anwendungen, die eine einfache, ereignisgesteuerte Umschaltung erfordern. Die Verwendung von Adaptern gewährleistet eine saubere Kapselung und Wiederverwendbarkeit in modularen Steuerungsprojekten.