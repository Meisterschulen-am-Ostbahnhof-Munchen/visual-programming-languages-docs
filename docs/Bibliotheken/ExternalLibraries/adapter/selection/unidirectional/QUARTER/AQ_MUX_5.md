# AQ_MUX_5


![AQ_MUX_5](./AQ_MUX_5.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock `AQ_MUX_5` ist ein generischer Multiplexer für analoge Ausgänge (AQ). Er ermöglicht die Auswahl eines von fünf analogwertigen Eingangssignalen (über Adapter) und leitet dieses auf einen gemeinsamen analogen Ausgang weiter. Die Auswahl erfolgt über den Index `K`, der bei einer steigenden Flanke am Ereigniseingang `REQ` übernommen wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| `REQ` | Übernahme des Index `K` und Durchschalten des entsprechenden Eingangs auf den Ausgang |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| `CNF` | Bestätigung, dass der Index `K` übernommen und der Ausgang aktualisiert wurde |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `K` | `UINT` | Index für die Auswahl des Eingangs (0 = IN1, 1 = IN2, 2 = IN3, 3 = IN4, 4 = IN5) |

### **Daten-Ausgänge**
Keine separaten Datenausgänge; der ausgewählte Analogwert wird über den Adapter `OUT` bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket (Eingang) | `IN1` | `adapter::types::unidirectional::AQ` | 1. analoger Eingangswert |
| Socket (Eingang) | `IN2` | `adapter::types::unidirectional::AQ` | 2. analoger Eingangswert |
| Socket (Eingang) | `IN3` | `adapter::types::unidirectional::AQ` | 3. analoger Eingangswert |
| Socket (Eingang) | `IN4` | `adapter::types::unidirectional::AQ` | 4. analoger Eingangswert |
| Socket (Eingang) | `IN5` | `adapter::types::unidirectional::AQ` | 5. analoger Eingangswert |
| Plug (Ausgang) | `OUT` | `adapter::types::unidirectional::AQ` | Ausgang, der den Wert des ausgewählten Eingangs bereitstellt |

## Funktionsweise
Der Funktionsblock arbeitet ereignisgesteuert. Ein gültiger Index `K` (Wertebereich 0 bis 4) wird durch ein Ereignis am Eingang `REQ` übernommen. Sofort danach wird der analoge Wert des durch `K` bestimmten Eingangs (IN1 für K=0, IN2 für K=1, …, IN5 für K=4) auf den Ausgangsadapter `OUT` durchgeschaltet. Abschließend wird das Ereignis `CNF` gesendet, um die erfolgreiche Aktualisierung zu bestätigen. Bei ungültigen Werten für `K` (z. B. >4) bleibt der Ausgang unverändert und `CNF` wird dennoch ausgelöst (je nach Implementierung); die Spezifikation des konkreten Bausteins gibt hier das genaue Verhalten vor.

## Technische Besonderheiten
- **Generischer Baustein**: Der `AQ_MUX_5` wird in der 4diac-IDE als generischer FB instanziiert (GenericClassName `'GEN_AQ_MUX'`). Das ermöglicht eine flexible Anpassung der Typen oder Parameter durch das Entwicklungswerkzeug.
- **Unidirektionale Adapter**: Sowohl die Eingangs- als auch die Ausgangsadapter sind vom Typ `unidirectional::AQ`. Das bedeutet, der Datenfluss ist streng gerichtet (vom Socket zum Plug) und es findet keine Rückkopplung statt.
- **Echtzeitverhalten**: Der Baustein führt die Multiplex-Operation in einem einzigen Ereignisschritt aus, was besonders in zeitkritischen Steuerungen vorteilhaft ist.
- **Keine eigenen Datenausgänge**: Die gesamte analoge Ausgangsinformation wird ausschließlich über den Adapter-Plug `OUT` übertragen. Dies ermöglicht eine enge Kopplung mit nachfolgenden Adaptern der gleichen Schnittstelle.

## Zustandsübersicht
Der Funktionsblock besitzt intern mindestens zwei Zustände:
1. **Warten auf REQ** – Im Ruhezustand wird auf ein Ereignis am Eingang `REQ` gewartet.
2. **Umschalten und Bestätigen** – Nach dem Empfang von `REQ` wird der Index `K` ausgelesen, der zugehörige Eingang auf den Ausgang durchgeschaltet und das Ereignis `CNF` gesendet. Danach kehrt der Baustein in den Wartezustand zurück.

Diese einfache Zustandsmaschine garantiert eine schnelle und deterministische Reaktion.

## Anwendungsszenarien
- **Landtechnik** (ursprüngliches Einsatzgebiet): Auswahl verschiedener analoger Sensor- oder Stellsignale, z. B. zur Steuerung mehrerer Ventile oder zur Umschaltung zwischen verschiedenen Messwerten.
- **Industrielle Automatisierung**: Multiplexen von Analogsignalen in einer Leitwarte, etwa zur Überwachung mehrerer Messstellen über eine einzige Analogausgangskarte.
- **Test- und Simulationsumgebungen**: Einfaches Umschalten zwischen verschiedenen simulierten Analogwerten zu Testzwecken.

## Vergleich mit ähnlichen Bausteinen
- **AQ_MUX_2 / AQ_MUX_4**: Diese Bausteine bieten eine geringere Anzahl von Eingängen (2 bzw. 4). Der `AQ_MUX_5` erweitert die Flexibilität auf fünf Eingänge, was häufig für Anwendungen mit fünf parallelen Signalen benötigt wird.
- **AQ_MUX_5** vs. **Allgemeine Multiplexer (z. B. MUX_INT)**: Der hier beschriebene Baustein ist speziell für analoge Ausgangsschnittstellen (AQ) optimiert und setzt auf Adapter, während allgemeine Multiplexer standardisierte Datentypen und Ereignisse verwenden. Die Adapter-Kapselung erleichtert die Wiederverwendung und Typsicherheit.

## Fazit
Der `AQ_MUX_5` ist ein spezialisierter, generischer Multiplexer für analoge Ausgangsanwendungen im 4diac-Framework. Seine einfache Handhabung, die klare Ereignissteuerung und die Nutzung unidirektionaler Adapter machen ihn zu einem effizienten Werkzeug für die Auswahl eines von fünf analogen Signalen in Echtzeitsystemen.