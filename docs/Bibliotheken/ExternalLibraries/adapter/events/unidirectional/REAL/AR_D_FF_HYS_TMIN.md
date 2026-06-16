# AR_D_FF_HYS_TMIN


![AR_D_FF_HYS_TMIN](./AR_D_FF_HYS_TMIN.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AR_D_FF_HYS_TMIN** realisiert ein Data-Latch (D-Flip-Flop) mit einer Hysterese-Funktion sowie einer minimalen Wartezeit zwischen aufeinanderfolgenden Ausgabeereignissen am Ausgangsadapter. Er dient zur stabilen Erfassung und Weiterleitung von analogen Werten über unidirektionale AR-Adapter, wobei er Flankenrauschen unterdrückt und die Ausgabefrequenz begrenzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Beschreibung |
|----------|-------|--------------|
| INIT     | EInit | Initialisierungsanforderung; übergibt die Parameter HYSTERESIS und Tmin an die interne Logik. |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Beschreibung |
|----------|-------|--------------|
| INITO    | EInit | Bestätigung der erfolgten Initialisierung. |

### **Daten-Eingänge**

| Variable    | Typ  | Beschreibung |
|-------------|------|--------------|
| HYSTERESIS  | REAL | Hysterese-Band: Eine Änderung des Eingangswerts muss diesen Betrag überschreiten, damit ein neuer Wert gelatcht wird. |
| Tmin        | TIME | Mindestzeit zwischen zwei Ausgabeereignissen (inter-disposal time). Verhindert zu schnelles Weiterschalten. |

### **Daten-Ausgänge**
Der FB besitzt keine eigenständigen Datenausgänge; die Ausgabedaten werden über den Adapter **Q** bereitgestellt.

### **Adapter**

| Bezeichnung | Typ                                             | Richtung | Beschreibung |
|-------------|-------------------------------------------------|----------|--------------|
| **I**       | adapter::types::unidirectional::AR (Socket)     | Eingang  | Liefert den zu latchnden Wert über **I.D1** und das Taktsignal über **I.E1**. |
| **Q**       | adapter::types::unidirectional::AR (Plug)       | Ausgang  | Stellt den gelatchten Wert über **Q.D1** bereit und signalisiert eine Aktualisierung über **Q.E1**. |

## Funktionsweise

Der Baustein arbeitet intern mit einem Sub-FB vom Typ `logiBUS::signalprocessing::hysteresis::E_D_FF_ANY_HYS_TMIN` zusammen.

1. **Initialisierung**: Beim Ereignis **INIT** werden die Parameter **HYSTERESIS** und **Tmin** an die interne Logik übergeben. Nach erfolgreicher Initialisierung wird **INITO** ausgegeben.

2. **Datenerfassung**: Bei jedem Taktereignis am Adapter **I.E1** wird der aktuell anliegende Wert **I.D1** mit dem zuletzt gespeicherten Wert verglichen.

   - Eine Übernahme erfolgt nur, wenn die absolute Differenz zwischen **I.D1** und dem gespeicherten Wert größer als **HYSTERESIS** ist.
   - Ist die Differenz kleiner, bleibt der alte Wert unverändert (Hysterese-Funktion).

3. **Ausgabe mit Zeitbegrenzung**: Sobald der neue Wert übernommen wurde, wird das Ausgangssignal **Q.D1** aktualisiert. Das zugehörige Ereignis **Q.E1** wird jedoch nur dann gesendet, wenn seit dem letzten **Q.E1** mindestens die Zeitspanne **Tmin** vergangen ist. Dadurch wird die maximale Ausgabefrequenz begrenzt.

Das gesamte Verhalten kann als taktgesteuerter, hysteresebehafneter Signalhaltebaustein mit Ausgabesperre betrachtet werden.

## Technische Besonderheiten

- **Hysterese**: Unterdrückt Rauschen und kleine Schwankungen des Eingangssignals. Erst wenn die Änderung den Wert **HYSTERESIS** überschreitet, wird ein neuer Zustand angenommen.
- **Minimale Intervallzeit (Tmin)**: Verhindert eine zu hohe Ereignisrate am Ausgang. Dies ist insbesondere bei nachgeschalteten, rechenintensiven oder kommunikationsbegrenzten Systemen vorteilhaft.
- **Adapterbasierte Schnittstellen**: Sowohl Eingang als auch Ausgang verwenden den unidirektionalen AR-Adapter, der Daten und Ereignis kombiniert. Dies vereinfacht die modulare Verkettung von Signalverarbeitungsbausteinen.

## Zustandsübersicht

Der FB besitzt keinen expliziten FSM (endlichen Automaten) in der oberen Ebene, da die Zustandslogik im internen Sub-FB gekapselt ist. Das logische Verhalten entspricht jedoch einem D-Flip-Flop mit erweiterten Bedingungen:

- **Ruhezustand**: Warten auf den nächsten Takt (I.E1).
- **Prüfzustand**: Vergleich des neuen Werts mit dem gespeicherten Wert unter Berücksichtigung der Hysterese.
- **Ausgabezustand**: Aktualisierung von **Q.D1** und, sofern **Tmin** abgelaufen ist, Senden von **Q.E1**.

Eine grafische Zustandsmaschine kann bei Bedarf aus dem internen Sub-FB abgeleitet werden.

## Anwendungsszenarien

- **Messwerterfassung mit Rauschunterdrückung**: Glätten von Sensorsignalen (z. B. Temperatur, Druck) und Weitergabe nur bei signifikanten Änderungen.
- **Zeitgesteuerte Prozessausgaben**: Steuerung von Aktoren, die nicht schneller als eine vorgegebene Taktfrequenz angesteuert werden dürfen.
- **Signalaufbereitung in Feldbussystemen**: Reduzierung der Buslast durch Begrenzung der Ereignisrate, ohne Informationsverlust durch Hysterese.
- **Kaskadierung von Flip-Flops**: Einsatz als stabilisierte Zwischenstufe in Datenketten mit mehreren Abtaststufen.

## Vergleich mit ähnlichen Bausteinen

- **Einfaches D-Flip-Flop (z. B. E_D_FF)**: Besitzt weder Hysterese noch Ausgabezeitbegrenzung. Ändert seinen Ausgang bei jedem Takt, unabhängig von der Änderungsgröße oder Frequenz.
- **Hysterese-Flip-Flop (z. B. E_D_FF_HYS)**: Enthält die Hysterese, aber keine minimale Intervallzeit. Ereignisse können sehr schnell aufeinander folgen, wenn die Hysterese ständig überschritten wird.
- **Begrenztes Flip-Flop (ohne Hysterese)**: Nur die minimale Ausgabezeit wird eingehalten; kleine Wertänderungen werden dennoch sofort verarbeitet, was zu Oszillationen führen kann.

Der **AR_D_FF_HYS_TMIN** vereint beide Mechanismen und bietet damit eine robuste Lösung für praktische Mess- und Steuerungsaufgaben.

## Fazit

Der Funktionsblock **AR_D_FF_HYS_TMIN** ist ein vielseitiges Werkzeug zur verlässlichen Signalweiterleitung in Automatisierungssystemen. Durch die Kombination von Hysterese und minimaler inter-disposal time werden typische Probleme wie Rauschen, Flimmern und Überlastung nachgeschalteter Verarbeitungsstufen effektiv vermieden. Die adapterbasierte Schnittstelle erleichtert die Einbindung in bestehende modulare Architekturen.