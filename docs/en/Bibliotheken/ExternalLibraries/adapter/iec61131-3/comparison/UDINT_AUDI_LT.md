# UDINT_AUDI_LT
![UDINT_AUDI_LT](./UDINT_AUDI_LT.svg)
* * * * * * * * * *
## Introduction
The function block **UDINT_AUDI_LT** performs a numerical less-than comparison according to IEC 61131-3. It compares two input values and returns the result (true/false) via an output adapter. The internal processes are implemented as a sub-application using a standardized comparison block (F_LT).
## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|------|--------|-----------------------------|

| REQ | Event | Trigger for the comparison process |

### **Event Outputs**

| Name | Type | Description |

|------|--------|-----------------------------|

| (via adapter OUT.E1) | Event | Acknowledgement after successful comparison |

The event output is implemented via the **OUT** adapter (type `AX`).

### **Data Inputs**

| Name | Type | Description |

|------|-------------------|-----------------------------|

| IN1 | ANY_ELEMENTARY | First comparison value |

| IN2 | (via socket adapter) | Second comparison value |

The second comparison value is read via a socket adapter **IN2** (type `AUDI`).

### **Data Outputs**

| Name | Type | Description |

|------|-------------------|-----------------------------|

| (via adapter OUT.D1) | (implicit) | Comparison result (TRUE/FALSE) |

The result is output as a logical value via adapter **OUT** (type `AX`).

### **Adapter**

| Name | Type | Direction | Description |

|-------|--------|------------|--------------------------------------|

| OUT | AX | Plug | Output adapter for result and event |

| IN2 | AUDI | Socket | Input adapter for the second comparison value |

## Functionality
The block is activated when an event occurs at input **REQ** or socket input **IN2.E1**. The values from **IN1** (direct data input) and **IN2** (provided via the socket adapter) are then fed to the internal function block **F_LT** (IEC 61131-3 comparison block "<“) übergeben. Das Ergebnis der Operation wird über den Adapter **OUT** als Datenwert (D1) und gleichzeitig ein Bestätigungsereignis (E1) ausgegeben.

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
| **UDINT_AUDI_GT** | Größer (>") | Analog Adapter Structure |

| **UDINT_AUDI_EQ** | Equal (==) | Analog Adapter Structure |

| **F_LT** | Less than (<) | Classic Inputs/Outputs |

Unlike direct comparison blocks such as `F_LT`, this block offers extended coupling via adapters, simplifying integration into modular automation architectures.

## Conclusion
The function block **UDINT_AUDI_LT** is an IEC 61131-3 compliant implementation of a less-than comparison. The use of adapters for the second input and the output enables flexible integration into applications with hierarchical or plug-and-play interfaces. is particularly suitable for control tasks where comparison results need to be further processed in an event-driven manner.