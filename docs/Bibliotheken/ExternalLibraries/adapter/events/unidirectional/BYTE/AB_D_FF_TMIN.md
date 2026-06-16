# AB_D_FF_TMIN


![AB_D_FF_TMIN](./AB_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung

Der **AB_D_FF_TMIN** ist ein Adapter-basierter Funktionsbaustein (FB) nach IEC 61499, der die Funktionalität eines Data-Latch (D-Flipflop) mit einer minimalen Zeitbedingung zwischen aufeinanderfolgenden Ausgangsereignissen realisiert. Er dient dazu, einen digitalen Datenwert von einem Adapter-Socket (Eingang) auf einen Adapter-Plug (Ausgang) zu übertragen und dabei sicherzustellen, dass die Ausgangsereignisse (EO) nicht schneller als durch einen konfigurierten Zeitparameter `Tmin` erlaubt auftreten. Der Baustein abstrahiert die reine D-Flipflop-Logik durch die Nutzung eines internen Flipflop-Bausteins und kapselt Daten und Ereignisse in Adapter-Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name   | Typ    | Kommentar                           |
|--------|--------|-------------------------------------|
| `INIT` | EInit  | Initialisierungsanforderung (setzt die minimale Zeit) |

### **Ereignis-Ausgänge**

| Name    | Typ    | Kommentar                           |
|---------|--------|-------------------------------------|
| `INITO` | EInit  | Initialisierungsbestätigung         |

### **Daten-Eingänge**

| Name   | Typ  | Kommentar                                      |
|--------|------|------------------------------------------------|
| `Tmin` | TIME | Mindestzeit zwischen zwei Ausgangsereignissen EO |

### **Daten-Ausgänge**
Keine direkten Datenausgänge; die Datenausgabe erfolgt über den Adapter-Plug `Q`.

### **Adapter**

| Richtung | Name | Typ                              | Kommentar                                                   |
|----------|------|----------------------------------|-------------------------------------------------------------|
| Socket   | `I`  | adapter::types::unidirectional::AB | Eingangsadapter: liefert Ereignis `E1` und Datenwert `D1` (der zu latchende Wert) |
| Plug     | `Q`  | adapter::types::unidirectional::AB | Ausgangsadapter: gibt den gelatchten Datenwert `D1` sowie das Ereignis `E1` aus |

*Hinweis:* Der Adapter `unidirectional::AB` definiert ein Ereignis `E1` und einen Datenwert `D1` (typischerweise ein boolescher oder beliebiger generischer Typ). Die genaue Typdefinition des Adapters liegt außerhalb dieses Bausteins.

## Funktionsweise

Der Baustein arbeitet intern mit dem FB `E_D_FF_ANY_TMIN` (Typ `iec61499::events::E_D_FF_ANY_TMIN`), der die Kernlogik des D-Flipflops mit einer minimalen Haltezeit zwischen Ausgangsereignissen realisiert. Die Funktionsweise gliedert sich wie folgt:

1. **Initialisierung:**  
   Durch ein Ereignis an `INIT` wird der Parameter `Tmin` (Mindestzeit) an den inneren FB übergeben. Der Baustein quittiert dies mit `INITO`.

2. **Datenerfassung und -weitergabe:**  
   - Am Socket `I` tritt ein Ereignis `E1` auf, das den Datenwert `D1` (das zu latchende Signal) transportiert.  
   - Dieses Ereignis wird als `CLK` an den inneren Flipflop-Baustein weitergeleitet, der gleichzeitig den Datenwert `D1` von `I.D1` aufnimmt.  
   - Der innere Flipflop speichert den Wert `D1` und gibt ihn an seinem Ausgang `Q` aus.  
   - Der gelatchte Wert wird über den Plug `Q.D1` nach außen gegeben, und zeitgleich wird das Ausgangsereignis `EO` des inneren FBs ausgelöst.  
   - Dieses `EO` wird an `Q.E1` weitergeleitet, sodass der empfangende Adapter über die Aktualisierung informiert wird.

3. **Zeitsteuerung:**  
   Der innere FB `E_D_FF_ANY_TMIN` stellt sicher, dass nach einem Ausgangsereignis `EO` für die Dauer von `Tmin` kein weiteres Ausgangsereignis erzeugt werden kann – unabhängig davon, wie schnell Eingangsereignisse eintreffen. Überschreitet die Zeit zwischen zwei `E1`-Eingängen die `Tmin`-Schranke, wird der Wert sofort übernommen, andernfalls wird er blockiert, bis die Mindestzeit abgelaufen ist.

## Technische Besonderheiten

- **Adapter-basierte Schnittstelle:**  
  Statt einzelner Ereignis-/Datenports verwendet der Baustein Adapter, die Ereignis und Daten als gekapselte Einheit transportieren. Dies erhöht die Wiederverwendbarkeit und reduziert die Anzahl äußerer Verbindungen.

- **Minimale Ausgabezeit (Tmin):**  
  Die Einstellung `Tmin` verhindert ein zu schnelles Auslösen von Ausgangsereignissen, was in zeitkritischen Steuerungen (z. B. zur Entprellung oder zur Einhaltung von Verarbeitungszyklen) nützlich ist.

- **Interne Nutzung eines spezialisierten FB:**  
  Der Baustein delegiert die eigentliche Flipflop-Logik an den systeminternen FB `E_D_FF_ANY_TMIN`, der für die korrekte zeitliche Steuerung zuständig ist. Dies hält den äußeren FB schlank und fehlerfrei.

- **Typisierter Adapter:**  
  Der Adaptertyp `adapter::types::unidirectional::AB` ist als unidirektional definiert: Daten und Ereignisse fließen nur in eine Richtung (vom Socket zum Plug). Dadurch ist der FB strikt aufwärtskompatibel.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten sichtbaren Zustandsautomaten; der Zustand ergibt sich aus dem inneren Flipflop und der Zeitsteuerung:

- **Zustand 0 (initial / nicht gelatcht):** Nach INIT oder nach einem Reset (nicht explizit vorhanden) liegt undefinierter Zustand vor. Der Wert `Q.D1` wird erst nach dem ersten gültigen `E1` am Socket gesetzt.
- **Zustand 1 (gelatcht und aktiv):** Der innere Flipflop hat einen Datenwert gespeichert. Nach einem Ausgangsereignis wird für die Dauer `Tmin` ein Sperrzustand eingehalten, in dem eingehende `E1`-Ereignisse ignoriert oder verzögert werden. Nach Ablauf der Mindestzeit ist der FB wieder bereit für die nächste Übernahme.

(Im XML ist kein SFC oder ECC definiert; die Zustandslogik liegt vollständig im internen Baustein.)

## Anwendungsszenarien

- **Entprellung von Signalen:**  
  Wenn ein Sensor oder eine Taste mehrere schnelle Impulse erzeugt (Prellen), kann der FB durch Setzen von `Tmin` auf z. B. 20 ms verhindern, dass mehrere Werte in kurzer Folge weitergereicht werden.

- **Zyklische Datenweitergabe mit Mindestabstand:**  
  In einer verteilten Steuerung soll ein Messwert nur in bestimmten Mindestintervallen an eine übergeordnete Komponente gesendet werden. Der FB dient als Puffer, der die Aktualisierungsrate begrenzt.

- **Sichere Übergabe in zeitkritischen Systemen:**  
  Bei der Übergabe eines Wertes von einem schnellen in einen langsameren Taktbereich kann der FB mit geeignetem `Tmin` Datenverlust oder Rauschen verhindern.

## Vergleich mit ähnlichen Bausteinen

| Baustein          | Eigenschaften                                                                 |
|-------------------|-------------------------------------------------------------------------------|
| **AB_D_FF**       | Reines D-Flipflop ohne minimale Ausgabezeit – Ereignisse werden sofort weitergegeben. |
| **E_D_FF_ANY**    | Standard-Ereignis-Daten-Flipflop ohne Zeitbeschränkung, aber mit diskreten Ports (keine Adapter). |
| **AB_D_FF_TMIN**  | Kombiniert Adapter-Kapselung mit einer konfigurierbaren Mindestzeit zwischen Ausgangsereignissen. |
| **R_TRIG / F_TRIG** | Detektieren von steigenden/fallenden Flanken – keine Funktionalität zum Latchen eines Datenwerts. |

Der **AB_D_FF_TMIN** hebt sich durch die Integration einer Zeitsteuerung in eine Adapter-basierte D-Flipflop-Logik ab und ist daher besonders für Anwendungen geeignet, die sowohl Datenlatching als auch zeitliche Entkopplung erfordern.

## Fazit

Der **AB_D_FF_TMIN** ist ein kompakter, adapterbasierter Funktionsbaustein, der die Grundfunktion eines D-Flipflops um die Fähigkeit erweitert, eine minimale Wartezeit zwischen Ausgangsereignissen einzuhalten. Durch die gekapselte Adapter-Schnittstelle und die interne Nutzung eines spezialisierten Flipflop-Bausteins wird eine hohe Wiederverwendbarkeit und klare Trennung von Logik und Zeitsteuerung erreicht. Der Baustein eignet sich insbesondere für industrielle Steuerungsanwendungen, bei denen Signalverarbeitung mit zeitlichen Randbedingungen erforderlich ist.