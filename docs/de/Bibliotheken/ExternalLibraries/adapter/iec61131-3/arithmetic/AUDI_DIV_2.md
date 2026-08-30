# AUDI_DIV_2


![AUDI_DIV_2](./AUDI_DIV_2.svg)

![AUDI_DIV_2](./AUDI_DIV_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein (FB) **AUDI_DIV_2** dient zur Durchführung einer arithmetischen Division. Es handelt sich hierbei um einen generischen Funktionsbaustein (`GEN_AUDI_DIV`), der flexibel mit verschiedenen Datentypen innerhalb der Adapter-Struktur arbeiten kann. Im Gegensatz zu klassischen mathematischen Bausteinen, die über dedizierte Dateneingänge verfügen, nutzt dieser Baustein Adapterverbindungen zur Kapselung von Signalen und Steuerungsflüssen.

## Schnittstellenstruktur

Der Baustein besitzt keine direkten klassischen Ereignis- oder Dateneingänge auf der Gehäuseoberfläche. Die gesamte Kommunikation wird über Adapter abgewickelt.

```
         +---------------------------------------+
         |              AUDI_DIV_2               |
         |                                       |
  [IN1] =|======================================>|=[OUT]
         | (unidirectional::AUDI)  (unidirect..) |
  [IN2] =|======================================>|
         | (unidirectional::AUDI)                |
         +---------------------------------------+
```

### **Ereignis-Eingänge**

*Keine direkten Ereigniseingänge vorhanden. Die Ereignissteuerung wird über die Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignisausgänge vorhanden. Die Ereignissteuerung wird über die Adapter abgewickelt.*

### **Daten-Eingänge**

*Keine direkten Dateneingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Datenausgänge vorhanden.*

### **Adapter**

| Typ | Name | Adaptertyp | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Socket** (Buchse) | `IN1` | `adapter::types::unidirectional::AUDI` | Erster Eingangswert für die Division (Dividend). |
| **Socket** (Buchse) | `IN2` | `adapter::types::unidirectional::AUDI` | Zweiter Eingangswert für die Division (Divisor). |
| **Plug** (Stecker) | `OUT` | `adapter::types::unidirectional::AUDI` | Ergebnis der Division (Quotient). |

---

## Funktionsweise

Der Baustein berechnet den Quotienten aus den über die Adapter `IN1` und `IN2` bereitgestellten Werten:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

Da die Schnittstellen als unidirektionale `AUDI`-Adapter ausgeführt sind, triggert eine Aktualisierung der Eingangswerte an `IN1` oder `IN2` (über die im Adapter integrierten Ereigniskanäle) die Berechnung im Funktionsbaustein. Das Ergebnis wird anschließend unmittelbar über das im `OUT`-Adapter gekapselte Ereignis signalisiert und an nachfolgende Bausteine weitergegeben.

---

## Technische Besonderheiten

- **Generischer Typ:** Der Baustein ist über das Attribut `eclipse4diac::core::GenericClassName` als `GEN_AUDI_DIV` deklariert. Dies ermöglicht eine automatische Typanpassung an die konkret verwendeten Datenstrukturen innerhalb der `AUDI`-Adapter.
- **Saubere Verdrahtung:** Durch die Kapselung von Daten- und Event-Signalen in Adaptern wird das visuelle "Spaghetticode"-Problem in 4diac-ide minimiert.
- **Fehlerbehandlung (Division durch Null):** Da es sich um eine generische Division handelt, fängt die zugrundeliegende Laufzeitumgebung (z.B. forte) eine Division durch Null ab, um einen Absturz der Steuerung zu verhindern. In einem solchen Fall wird der Ausgang typischerweise auf einen Standardwert (z.B. `0` oder `NaN`/`Infinity` je nach Datentyp) gesetzt.

---

## Zustandsübersicht

Die Ausführung folgt einem einfachen, ereignisgesteuerten Schema:

```
[Ereignis an IN1 oder IN2]
          │
          ▼
┌────────────────────────────────────────┐
│ Werte aus IN1 und IN2 einlesen         │
└────────────────────────────────────────┘
          │
          ▼
┌────────────────────────────────────────┐
│ Ist IN2 == 0?                          │
└──────────────────┬─────────────────────┘
                   │
         ┌─────────┴─────────┐
      JA │                NEIN
         ▼                   ▼
┌──────────────────┐ ┌───────────────────┐
│ Fehlerbehandlung │ │ OUT = IN1 / IN2   │
│ (z.B. OUT = 0)   │ └───────────────────┘
└────────┬─────────┘         │
         │                   │
         └─────────┬─────────┘
                   │
                   ▼
┌────────────────────────────────────────┐
│ Aktualisiere Daten im OUT-Adapter      │
└────────────────────────────────────────┘
          │
          ▼
[Sende Aktualisierungs-Event über OUT]
```

---

## Anwendungsszenarien

- **Skalierungs- und Normierungsaufgaben:** Division von Messwerten, die in standardisierten `AUDI`-Datenstrukturen übertragen werden.
- **Verhältnisberechnungen:** Bestimmung von Verhältnissen in der Prozessindustrie (z.B. Durchflussverhältnisse zweier Medien).
- **Signalverarbeitung:** Modularer Einsatz in Steuerungsarchitekturen, bei denen eine strikte Trennung durch Adapterstrukturen gefordert ist.

---

## Vergleich mit ähnlichen Bausteinen

| Baustein-Typ | Schnittstellenart | Verdrahtungsaufwand | Flexibilität |
| :--- | :--- | :--- | :--- |
| **Standard-`DIV`** | Einzelne Pins (REQ, IN1, IN2, OUT, CNF) | Hoch (viele Linien) | Gering (feste Datentypen pro Instanz) |
| **`AUDI_DIV_2`** | Adapter (`IN1`, `IN2`, `OUT`) | Sehr gering | Hoch (generische Anpassung über Adapter) |

---

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AUDI_DIV_2` ist ein moderner, adapterbasierter Funktionsbaustein für die IEC 61499. Er eignet sich hervorragend für komplexe Projekte in der 4diac-ide, bei denen ein hoher Wert auf Übersichtlichkeit, Kapselung und einfache Wartbarkeit des Applikationsdiagramms gelegt wird.
