# ADI_SUB_2

```
       +------------------------------------+
       |             ADI_SUB_2              |
       |                                    |
 IN1 ==# [ADI]                        [ADI] #== OUT
 IN2 ==# [ADI]                              |
       +------------------------------------+
```


![ADI_SUB_2](./ADI_SUB_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ADI_SUB_2` ist ein generischer Funktionsbaustein (Generic FB) zur Durchführung von arithmetischen Subtraktionen in IEC 61499 Anwendungen. Der Baustein nutzt unidirektionale Adapter des Typs `ADI`, um Eingangsdaten zu empfangen und das berechnete Ergebnis auszugeben. Durch den Einsatz von Adaptern wird die Verdrahtung innerhalb der 4diac-IDE vereinfacht und die Modularität erhöht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung wird vollständig über die angeschlossenen Adapter abgewickelt.

### **Ereignis-Ausgänge**

Der Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt über den Ausgangs-Adapter.

### **Daten-Eingänge**

Es sind keine direkten Daten-Eingänge definiert. Daten werden über die Eingangs-Adapter übergeben.

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge definiert. Das Ergebnis wird über den Ausgangs-Adapter bereitgestellt.

### **Adapter**

| Typ | Name | Adaptertyp | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Socket (Eingang)** | `IN1` | `adapter::types::unidirectional::ADI` | Erster Eingangswert (Minuend) für die Subtraktion. |
| **Socket (Eingang)** | `IN2` | `adapter::types::unidirectional::ADI` | Zweiter Eingangswert (Subtrahend) für die Subtraktion. |
| **Plug (Ausgang)** | `OUT` | `adapter::types::unidirectional::ADI` | Ergebnis (Differenz) der Subtraktion ($OUT = IN1 - IN2$). |

## Funktionsweise

Sobald an den Eingangs-Adaptern `IN1` oder `IN2` ein entsprechendes Berechnungsereignis signalisiert wird, führt der Baustein die Subtraktion aus:

$$\text{OUT} = \text{IN1} - \text{IN2}$$

Das Ergebnis wird an den Ausgangs-Adapter `OUT` übergeben, und das zugehörige Ausgangsereignis des Adapters wird ausgelöst, um nachfolgende Bausteine über den neuen Wert zu informieren.

## Technische Besonderheiten

- **Generischer Typ:** Der Baustein ist als generischer Typ definiert (`eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_ADI_SUB'`). Dies ermöglicht eine flexible Anpassung an unterschiedliche Datentypen innerhalb des `ADI`-Adapters.
- **Unidirektionale Adapter:** Durch die Verwendung der unidirektionalen Adapterstruktur (`adapter::types::unidirectional::ADI`) bleibt der Datenfluss gerichtet und zyklische Abhängigkeiten werden vermieden.

## Zustandsübersicht

Da es sich um einen mathematischen Berechnungsbaustein handelt, ist das Verhalten im Wesentlichen zustandslos und ereignisgesteuert:

1. **Warten:** Der Baustein wartet auf ein Trigger-Ereignis an einem der Eingangs-Adapter (`IN1` oder `IN2`).
2. **Berechnung:** Bei Ereigniseingang werden die Datenwerte ausgelesen und subtrahiert.
3. **Ausgabe:** Der berechnete Wert wird auf den Adapter `OUT` geschrieben und das dortige Sende-Ereignis getriggert.

## Anwendungsszenarien

- **Regelungstechnik:** Berechnung einer Regelabweichung ($e = w - x$), bei der Sollwert ($w$) und Istwert ($x$) über standardisierte ADI-Schnittstellen übertragen werden.
- **Messwertverarbeitung:** Differenzdruckmessung oder Offset-Korrektur von Sensorwerten, die über Adapter in die Applikation eingebunden sind.
- **Signalvorverarbeitung:** Reduzierung von Signalwerten um feste oder variable Grenzwerte vor der Weiterleitung an Aktoren.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Subtraktionsbaustein (wie z.B. dem klassischen `SUB`-Baustein nach IEC 61131-3), der direkte Daten- und Ereignispins nutzt, bietet `ADI_SUB_2` folgende Vorteile:

- **Weniger Verbindungslinien:** Daten und Ereignisse sind im `ADI`-Adapter gebündelt, was das Anwendungsdiagramm in 4diac übersichtlicher macht.
- **Standardisierte Schnittstellen:** Erleichtert den Austausch von Berechnungs- und Verarbeitungsblöcken, da nur noch die Adapter verbunden werden müssen.

- **[`ADI_SUB_2_UNGATED`](ADI_SUB_2_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ADI_SUB_2` ist ein effizienter Hilfsbaustein für strukturierte IEC 61499 Steuerungsanwendungen. Er eignet sich hervorragend für anspruchsvolle Architekturen, bei denen Übersichtlichkeit und standardisierte Adapter-Schnittstellen im Vordergrund stehen.
