# UDINT_AUDI_LT


![UDINT_AUDI_LT](./UDINT_AUDI_LT.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **UDINT_AUDI_LT** realisiert einen numerischen Kleiner-Vergleich (less than) nach IEC 61131-3. Er vergleicht zwei Eingangswerte und liefert das Ergebnis (wahr/falsch) über einen Ausgangs-Adapter. Die internen Abläufe sind als Sub-Applikation mit einem standardisierten Vergleichsbaustein (F_LT) umgesetzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ    | Beschreibung                 |
|------|--------|-----------------------------|
| REQ  | Event  | Auslöser für den Vergleichsprozess |

### **Ereignis-Ausgänge**
| Name | Typ    | Beschreibung                 |
|------|--------|-----------------------------|
| (über Adapter OUT.E1) | Event  | Quittung nach erfolgreichem Vergleich |

Der Ereignisausgang wird über den Adapter **OUT** (Typ `AX`) realisiert.

### **Daten-Eingänge**
| Name | Typ               | Beschreibung                 |
|------|-------------------|-----------------------------|
| IN1  | ANY_ELEMENTARY    | Erster Vergleichswert        |
| IN2  | (über Socket-Adapter) | Zweiter Vergleichswert      |

Der zweite Vergleichswert wird über einen Socket-Adapter **IN2** (Typ `AUDI`) eingelesen.

### **Daten-Ausgänge**
| Name | Typ               | Beschreibung                 |
|------|-------------------|-----------------------------|
| (über Adapter OUT.D1) | (implizit) | Vergleichsergebnis (TRUE/FALSE) |

Das Ergebnis wird über den Adapter **OUT** (Typ `AX`) als logischer Wert ausgegeben.

### **Adapter**
| Name  | Typ    | Richtung   | Beschreibung                        |
|-------|--------|------------|-------------------------------------|
| OUT   | AX     | Plug       | Ausgangsadapter für Ergebnis und Ereignis |
| IN2   | AUDI   | Socket     | Eingangsadapter für den zweiten Vergleichswert |

## Funktionsweise
Bei einem Ereignis am Eingang **REQ** oder am Socket-Eingang **IN2.E1** wird der Baustein aktiviert. Anschließend werden die Werte von **IN1** (direkter Dateneingang) und **IN2** (über den Socket-Adapter bereitgestellt) dem internen Baustein **F_LT** (IEC 61131-3 Vergleichsbaustein „<“) übergeben. Das Ergebnis der Operation wird über den Adapter **OUT** als Datenwert (D1) und gleichzeitig ein Bestätigungsereignis (E1) ausgegeben.

Die Verwendung von Adaptern ermöglicht eine lose Kopplung der Eingabe- und Ausgabedaten.

## Technische Besonderheiten
- **Datentypen** – IN1 akzeptiert jeden elementaren Typ (ANY_ELEMENTARY); IN2 ist durch den verwendeten Adaptertyp (`AUDI`) festgelegt.
- **Adapter-Schnittstelle** – Die Ereignis- und Datenausgabe erfolgt nicht über klassische Ein-/Ausgänge, sondern über einen Plug-Adapter. Das ermöglicht eine flexible Anbindung an nachfolgende Bausteine.
- **Interne Realisierung** – Der Vergleich wird nicht direkt im Baustein selbst berechnet, sondern delegiert an den in IEC 61131-3 definierten Funktionsbaustein `F_LT`. Somit ist die Implementierung konsistent zur Norm.

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine. Die Verarbeitung erfolgt ereignisgesteuert – nach jedem Eingangsereignis wird der Vergleich einmal ausgeführt und das Ergebnis unverzögert ausgegeben. Es werden keine internen Zustände gehalten.

## Anwendungsszenarien
- **Schwellwertüberwachung** – Prüfen, ob ein Messwert (IN1) unter einem Grenzwert (IN2) liegt.
- **Sicherheitslogik** – Erkennen von Unterläufen oder Bereichsunterschreitungen.
- **Steuerungssequenzen** – Aktivieren eines nachfolgenden Prozessschrittes nur wenn eine Bedingung `IN1 < IN2` erfüllt ist.
- **Parametrierbare Bibliotheksbausteine** – Durch die Adapter-Schnittstelle kann der zweite Vergleichswert oft von einer übergeordneten Konfiguration bereitgestellt werden.

## Vergleich mit ähnlichen Bausteinen
| Baustein       | Funktion          | Schnittstelle                      |
|----------------|-------------------|------------------------------------|
| **UDINT_AUDI_LT** | Kleiner (<)       | Adapter-basiert (IN2, OUT)         |
| **UDINT_AUDI_GT** | Größer (>)        | Analoge Adapter-Struktur            |
| **UDINT_AUDI_EQ** | Gleich (==)       | Analoge Adapter-Struktur            |
| **F_LT**          | Kleiner (<)       | Klassische Ein-/Ausgänge            |

Im Gegensatz zu direkten Vergleichsbausteinen wie `F_LT` bietet dieser Baustein eine erweiterte Kopplung durch Adapter, was die Integration in modulare Automatisierungsarchitekturen vereinfacht.

## Fazit
Der Funktionsbaustein **UDINT_AUDI_LT** ist eine IEC 61131-3 konforme Implementierung eines Kleiner-Vergleichs. Durch die Verwendung von Adaptern für den zweiten Eingang und den Ausgang wird eine flexible Einbindung in Applikationen mit hierarchischen oder plug&play-artigen Schnittstellen ermöglicht. Er eignet sich besonders für Steuerungsaufgaben, bei denen Vergleichsergebnisse ereignisgesteuert weiterverarbeitet werden müssen.