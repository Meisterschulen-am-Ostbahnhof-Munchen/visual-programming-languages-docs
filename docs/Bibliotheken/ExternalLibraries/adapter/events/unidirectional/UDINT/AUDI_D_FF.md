# AUDI_D_FF


![AUDI_D_FF](./AUDI_D_FF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_D_FF** realisiert ein taktgesteuertes D‑Flip‑Flop (Data Latch) auf Basis von IEC 61499‑Adaptern. Er übernimmt bei einem Ereignis am Eingangsadapter den anliegenden Datenwert, speichert ihn und gibt ihn über den Ausgangsadapter aus. Der Baustein kapselt die gesamte Steuerlogik in einem kompakten, adapterbasierten Interface und erlaubt so eine saubere Trennung von Ereignis- und Datenkommunikation.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine – die Ereignissteuerung erfolgt ausschließlich über den Socket‑Adapter.

### **Ereignis-Ausgänge**
Keine – die Ereignisausgabe erfolgt ausschließlich über den Plug‑Adapter.

### **Daten-Eingänge**
Keine – die Datenaufnahme erfolgt ausschließlich über den Socket‑Adapter.

### **Daten-Ausgänge**
Keine – die Datenausgabe erfolgt ausschließlich über den Plug‑Adapter.

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
|------------|-----|----------|--------------|
| **I**      | `adapter::types::unidirectional::AUDI` | Socket (Eingang) | Liefert das Taktereignis (E1) und den zu übernehmenden Datenwert (D1). |
| **Q**      | `adapter::types::unidirectional::AUDI` | Plug (Ausgang)  | Gibt das Ausgangsereignis (E1) und den gespeicherten Datenwert (D1) aus. |

Beide Adapter sind vom gleichen unidirektionalen Typ **AUDI**, der ein Ereignis und einen Datenwert gemeinschaftlich transportiert. Der Socket **I** dient als Quelle, der Plug **Q** als Senke.

## Funktionsweise
Der FB arbeitet nach der klassischen D‑Flip‑Flop‑Funktion:

1. **Warten auf Takt**: Solange kein Ereignis am Eingang **I.E1** anliegt, behält der interne Speicher seinen letzten Wert bei.
2. **Übernahme bei Taktflanke**: Ein Ereignis an **I.E1** (als positive Flanke interpretiert) veranlasst den Baustein, den aktuellen Datenwert von **I.D1** zu übernehmen und im internen Speicher abzulegen.
3. **Ausgabe**: Nach der Übernahme wird ein Ereignis am Ausgang **Q.E1** ausgegeben und der gespeicherte Datenwert erscheint an **Q.D1**. Dieser Wert bleibt stabil, bis das nächste Taktereignis eintrifft.

Die interne Implementierung verwendet den IEC‑61499‑Standardbaustein `E_D_FF_ANY`, der eine typunabhängige D‑Flip‑Flop‑Funktion bereitstellt. Die Adapter **I** und **Q** sind direkt mit dessen Ereignis- und Daten‑Ports verschaltet.

## Technische Besonderheiten
- **Adapter‑basierte Schnittstelle**: Der FB nutzt keine einzelnen Ereignis- oder Daten‑Ein‑/Ausgänge, sondern kommuniziert ausschließlich über unidirektionale Adapter. Dies vereinfacht die Verbindung in komplexen Netzwerken und unterstützt eine modulare Typprüfung.
- **Typunabhängigkeit**: Der interne Baustein `E_D_FF_ANY` arbeitet mit beliebigen Datentypen (ANY). Der eigentliche Datentyp wird durch die Adapterdefinition des Typs `AUDI` festgelegt.
- **Unidirektionale Kommunikation**: Der Adaptertyp `adapter::types::unidirectional::AUDI` überträgt Ereignis und Daten nur in eine Richtung – vom Socket zum Plug. Eine Rückkopplung ist nicht vorgesehen.
- **Kein zusätzlicher Initialisierungszustand**: Der FB startet ohne definierten Datenwert; der interne Zustand entspricht dem Initialzustand des verwendeten `E_D_FF_ANY`‑Bausteins.

## Zustandsübersicht
Da es sich um einen rein kombinatorischen, ereignisgesteuerten Speicher handelt, kann das Verhalten durch zwei stabile Zustände beschrieben werden:

- **Zustand A (Warten)**: Kein Taktereignis empfangen – der Ausgang **Q.D1** hält den zuletzt übernommenen Wert.
- **Zustand B (Übernahme)**: Ein Taktereignis an **I.E1** löst die Übernahme von **I.D1** aus. Nach der Verarbeitung kehrt der FB sofort wieder in den Wartezustand zurück (kein mehrstufiger Automat).

Eine grafische Darstellung als Zustandsautomat entfällt, da die Logik auf den internen `E_D_FF_ANY` delegiert wird, dessen Zustandsdiagramm in der IEC 61499‑Spezifikation definiert ist.

## Anwendungsszenarien
- **Datenpuffer**: Übernehmen eines Sensorsignals zu einem definierten Messzeitpunkt und Weiterleiten an eine Steuerung.
- **Synchronisation**: Gleichzeitiges Auslesen mehrerer Datenquellen durch ein gemeinsames Taktereignis.
- **Realisation von Registern**: Mehrere `AUDI_D_FF`‑Bausteine können parallel geschaltet werden, um ein n‑Bit‑Register aufzubauen.
- **Schnittstelle zu ereignisgesteuerten Kommunikationsprotokollen**: Der Adapter eignet sich besonders für Systeme, die standardisierte Daten‑Ereignis‑Paare verwenden (z. B. OPC UA oder MQTT‑Anbindungen).

## Vergleich mit ähnlichen Bausteinen
- **`E_D_FF_ANY`** (IEC 61499‑Standardbausstein): Besitzt separate Ereignis- und Daten‑Ein‑/Ausgänge, kein Adapterinterface. Der `AUDI_D_FF` kapselt diese Schnittstellen in einem Adapter und vereinfacht so die Verwendung in adapterbasierten Netzwerken.
- **SR‑Flip‑Flop (Set‑Reset)**: Hat zwei Dateneingänge (Set/Reset) und erlaubt keinen reinen Taktbetrieb. Der `AUDI_D_FF` ist auf den einfachen D‑Flip‑Flop‑Anwendungsfall zugeschnitten.
- **AUDI‑Adapter‑basierte Bausteine (z. B. `AUDI_D_FF_2`)** : Andere Implementierungen könnten zusätzliche Logik wie asynchronen Reset enthalten. Der vorliegende FB realiert das minimale D‑Flip‑Flop ohne zusätzliche Steuerfunktionen.

## Fazit
Der **AUDI_D_FF** stellt eine sauber gekapselte, adapterbasierte Realisierung eines D‑Flip‑Flops dar. Durch den Einsatz des unidirektionalen `AUDI`‑Adaptertyps wird die Schnittstelle auf das Wesentliche reduziert – ein Ereignis und ein Datenwert pro Seite. Die interne Nutzung des bewährten `E_D_FF_ANY`‑Bausteins gewährleistet eine robuste, standardkonforme Funktion. Der FB eignet sich besonders für modulare Architekturen, die auf Adapter‑Konnektivität setzen, und erleichtert die Wiederverwendung in verschiedenen Steuerungsprojekten.