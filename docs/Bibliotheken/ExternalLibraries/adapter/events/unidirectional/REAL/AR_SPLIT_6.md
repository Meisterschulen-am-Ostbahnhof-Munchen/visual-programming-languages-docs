# AR_SPLIT_6


![AR_SPLIT_6](./AR_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AR_SPLIT_6** dient dazu, einen einzelnen AR-Adapter-Eingang auf sechs separate AR-Adapter-Ausgänge zu verteilen. Er ist als generischer Baustein (Generic FB) ausgelegt und ermöglicht eine einfache Vervielfachung einer AR-Schnittstelle ohne Datenverlust oder protokollspezifische Umwandlung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden. Die Funktionalität wird rein über die Adapter-Schnittstelle gesteuert.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|-------------|
| `adapter::types::unidirectional::AR` | **IN** | Socket (Eingang) | Ein eingehender AR-Adapter, der auf alle Ausgänge verteilt wird. |
| `adapter::types::unidirectional::AR` | **OUT1** | Plug (Ausgang) | Erster ausgehender AR-Adapter (identisch mit IN). |
| `adapter::types::unidirectional::AR` | **OUT2** | Plug (Ausgang) | Zweiter ausgehender AR-Adapter (identisch mit IN). |
| `adapter::types::unidirectional::AR` | **OUT3** | Plug (Ausgang) | Dritter ausgehender AR-Adapter (identisch mit IN). |
| `adapter::types::unidirectional::AR` | **OUT4** | Plug (Ausgang) | Vierter ausgehender AR-Adapter (identisch mit IN). |
| `adapter::types::unidirectional::AR` | **OUT5** | Plug (Ausgang) | Fünfter ausgehender AR-Adapter (identisch mit IN). |
| `adapter::types::unidirectional::AR` | **OUT6** | Plug (Ausgang) | Sechster ausgehender AR-Adapter (identisch mit IN). |

## Funktionsweise

Der Baustein leitet die Signale des eingehenden AR-Adapters (Socket **IN**) unverändert an alle sechs Ausgangs-Adapter (**OUT1** … **OUT6**) weiter. Es findet keine logische oder zeitliche Verarbeitung statt – jede Änderung am Eingang wird sofort auf allen Ausgängen sichtbar. Der FB arbeitet rein passiv und benötigt keine Ereignissteuerung.

## Technische Besonderheiten

- **Generischer Baustein (Generic FB):** Der FB ist als generischer Typ deklariert (`eclipse4diac::core::GenericClassName = 'GEN_AR_SPLIT'`), sodass er in verschiedenen Kontexten wiederverwendet werden kann, ohne den zugrundeliegenden AR-Typ neu definieren zu müssen.
- **Unidirektionale Adapter:** Alle verwendeten Adapter sind vom Typ `adapter::types::unidirectional::AR`, d.h. die Daten fließen nur vom Socket zu den Plugs.
- **Keine Zustandsmaschine:** Da der FB keine Ereignisse oder interne Logik besitzt, existiert kein ECC (Execution Control Chart).

## Zustandsübersicht

Dieser FB enthält keine Zustandsmaschine. Er arbeitet datengetrieben und stellt die Ein-/Ausgangsbeziehung kontinuierlich und ohne Verzögerung her.

## Anwendungsszenarien

- **Verteilen eines AR-Signals an mehrere Verbraucher:** Wenn ein Sensor oder Aktor seine Daten über einen AR-Adapter bereitstellt, können mit diesem FB mehrere nachgeschaltete Module parallel versorgt werden (z.B. mehrere Regler oder Anzeigen).
- **Test- und Simulationsumgebungen:** Der FB eignet sich, um ein einzelnes Testsignal auf mehrere Auswerteeinheiten gleichzeitig zu schalten.
- **Redundanz oder Parallelisierung:** In Steuerungen, die mehrere identische Verarbeitungsketten benötigen, wird der Eingang einfach dupliziert.

## Vergleich mit ähnlichen Bausteinen

- **AR_SPLIT_2 / AR_SPLIT_4:** Diese Bausteine teilen den Eingang auf zwei bzw. vier Ausgänge auf und unterscheiden sich nur in der Anzahl der Ausgänge. Der AR_SPLIT_6 erweitert dies auf sechs Ausgänge.
- **Allgemeine Split-FBs:** Es existieren weitere Split-Bausteine für Datentypen (z.B. INT_SPLIT), die jedoch auf spezifische Datenformate ausgelegt sind. Dieser FB arbeitet ausschließlich auf Adapterebene und ist dadurch flexibler, wenn der Datenaustausch über Adapter erfolgt.
- **Eigene Implementierung:** Alternativ könnte die Aufteilung auch durch manuelles Verkabeln mehrerer Adapterknoten erfolgen, was jedoch die Übersichtlichkeit und Wartbarkeit verschlechtert.

## Fazit

Der **AR_SPLIT_6** ist ein einfacher, aber nützlicher generischer Baustein zur Vervielfachung eines AR-Adapter-Signals auf sechs parallele Ausgänge. Er zeichnet sich durch minimale Komplexität, klare Struktur und hohe Wiederverwendbarkeit in Automatisierungsprojekten aus, die auf der 4diac-IDE und dem IEC 61499-Standard basieren.