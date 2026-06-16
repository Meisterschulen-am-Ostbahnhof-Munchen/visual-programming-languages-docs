# AUDI_D_FF_HYS


![AUDI_D_FF_HYS](./AUDI_D_FF_HYS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AUDI_D_FF_HYS` realisiert ein datengetriggertes Flip‑Flop (D‑Latch) mit einer Hysteresefunktion. Er dient dazu, einen eingehenden Datenwert bei einem Ereignis zu übernehmen, wobei durch die Hysterese ein Schaltverhalten mit definiertem Totband ermöglicht wird. Der Baustein kapselt die Logik des internen Bausteins `E_D_FF_ANY_HYS` und stellt die Schnittstellen über zwei unidirektionale Adapter vom Typ `AUDI` bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Typ   | Kommentar       | Mit Variable |
|----------|-------|-----------------|--------------|
| `INIT`   | EInit | Set Hysteresis  | `HYSTERESIS` |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Kommentar          |
|----------|-------|--------------------|
| `INITO`  | EInit | Init Confirmation  |

### **Daten-Eingänge**

| Variable      | Typ   | Kommentar        |
|---------------|-------|------------------|
| `HYSTERESIS`  | UDINT | Hysteresis band  |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – die Ausgabedaten werden über den Adapter `Q` bereitgestellt.

### **Adapter**

| Rolle   | Name | Typ (Adapter)               | Kommentar          |
|---------|------|-----------------------------|--------------------|
| Plug    | `Q`  | `adapter::types::unidirectional::AUDI` | Latched value     |
| Socket  | `I`  | `adapter::types::unidirectional::AUDI` | Value to latch    |

Der Adapter `AUDI` enthält jeweils einen Ereignis‑ und einen Datenkanal:  
- `I.E1`  – Ereignis, das den Latch‑Vorgang auslöst  
- `I.D1`  – Datenwert, der gelatcht werden soll  
- `Q.E1`  – Bestätigungsereignis nach erfolgreichem Latch  
- `Q.D1`  – der gelatchte (und hysteresebeeinflusste) Datenwert

## Funktionsweise
Der Baustein arbeitet als Wrapper um den internen Baustein `E_D_FF_ANY_HYS`. Beim Initialisierungsereignis `INIT` wird der Hysteresewert (an `HYSTERESIS`) übernommen; das `INITO`‑Ereignis bestätigt die Initialisierung.  
Während des Betriebs wird bei jedem Ereignis auf dem Adaptereingang `I.E1` der aktuelle Datenwert von `I.D1` übernommen und mit der eingestellten Hysterese verarbeitet. Das Ergebnis wird über den Adapterausgang `Q.D1` ausgegeben, begleitet von einem Ereignis `Q.E1`.  
Die Hysterese verhindert ein ständiges Umschalten bei geringen Signaländerungen: Der Ausgang wechselt seinen Zustand erst, wenn der Eingangswert das Hystereseband verlässt.

## Technische Besonderheiten
- Der Baustein nutzt die generische Implementierung `E_D_FF_ANY_HYS` (aus der Bibliothek `logiBUS::signalprocessing::hysteresis`).  
- Die Hysterese wird als `UDINT` (unsigned double integer) angegeben – der Wertebereich ist daher 0 … 4 294 967 295.  
- Die gesamte Ein‑/Ausgabe erfolgt ausschließlich über unidirektionale Adapter (`AUDI`), was eine klare Trennung und Wiederverwendbarkeit in komplexen Netzwerken fördert.  
- Das INIT‑Ereignis wird direkt an `INITO` durchgeschleift, ohne Zwischenverarbeitung – die Hysterese‑Einstellung erfolgt aber vor dem `INITO` (laut Datenverbindung).

## Zustandsübersicht
Da der FB eine reine Funktionsnetzwerk‑Verschaltung ist (kein eigenes ECC), ergibt sich der Zustand aus dem internen Baustein `E_D_FF_ANY_HYS`. Vereinfacht:
- **Rückgesetzt**: Ausgang `Q.D1` ist 0 oder einem definierten Initialwert.
- **Setzen**: Bei Überschreitung der oberen Hystereseschwelle wird der Ausgang auf 1 gesetzt.
- **Halten**: Bei Werten innerhalb des Hysteresebands bleibt der Ausgang unverändert.
- **Rücksetzen**: Bei Unterschreitung der unteren Hystereseschwelle wird der Ausgang zurückgesetzt.

## Anwendungsszenarien
- **Entprellung von Sensorsignalen**: Verhindert Flattern bei mechanischen Schaltern oder Näherungssensoren.  
- **Schwellwertschalter mit Rückkopplungsunterdrückung**: Z. B. Temperaturregelung mit einstellbarem Totband.  
- **Puffern digitaler Eingänge**: Übernahme eines stabilen Werts bei definiertem Ereignis (z. B. Taktflanke).  

## Vergleich mit ähnlichen Bausteinen
- **Standard‑D‑Flip‑Flop (ohne Hysterese)**: Reagiert sofort auf jede Änderung – keine Unterdrückung von Rauschen oder Prellen.  
- **RS‑Flip‑Flop mit Hysterese (z. B. `RS_FF_HYS`)**: Steuert über separate Set‑/Reset‑Ereignisse, während `AUDI_D_FF_HYS` einen einzigen Daten‑/Ereigniseingang nutzt.  
- **Schmitt‑Trigger‑Baustein**: Funktional ähnlich, aber meist ohne Latch‑/Speicherverhalten – hier wird der Wert bei einem Ereignis gelatcht und bis zum nächsten Ereignis gehalten.  

## Fazit
`AUDI_D_FF_HYS` kombiniert die Eigenschaften eines datengetriggerten Flip‑Flops mit einer einstellbaren Hysterese. Durch die Kapselung als Adapter‑Baustein lässt er sich leicht in modulare Automatisierungsnetzwerke einbinden und bietet eine robuste Lösung für Signalverarbeitung mit Entprellung oder Schwellwertlogik.