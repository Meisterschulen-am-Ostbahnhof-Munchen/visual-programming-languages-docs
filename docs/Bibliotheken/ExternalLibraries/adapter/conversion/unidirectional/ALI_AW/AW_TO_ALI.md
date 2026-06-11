# AW_TO_ALI


![AW_TO_ALI](./AW_TO_ALI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AW_TO_ALI** ist ein zusammengesetzter (Composite) Baustein, der einen unidirektionalen Adapter vom Typ **AW** (WORD) in einen Adapter vom Typ **ALI** (LINT) umwandelt. Er wird eingesetzt, um Daten zwischen verschiedenen Adapterschnittstellen zu konvertieren, ohne dass der Anwender die eigentliche Konvertierungslogik implementieren muss. Der Baustein nutzt intern den IEC 61131‑Funktionsbaustein `F_WORD_TO_LINT` und stellt die typische Ereignis‑/Datensteuerung über die mitgelieferten Adapter‑Schnittstellen bereit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Über den **Socket AW_IN** (Typ: `adapter::types::unidirectional::AW`) wird ein Ereignis vom Typ **E1** hereingeführt. Dieses Ereignis löst die Konvertierung des anliegenden Datenwerts aus.

### **Ereignis-Ausgänge**

Über den **Plug ALI_OUT** (Typ: `adapter::types::unidirectional::ALI`) wird nach erfolgreicher Konvertierung ein Ereignis **E1** ausgegeben. Es signalisiert, dass der konvertierte Wert am Datenausgang bereitsteht.

### **Daten-Eingänge**

Eingehende Daten werden über den **Socket AW_IN** geführt:
*   **D1** (Datentyp: WORD) – der zu konvertierende 16‑Bit‑Wert.

### **Daten-Ausgänge**

Die konvertierten Daten werden über den **Plug ALI_OUT** ausgegeben:
*   **D1** (Datentyp: LINT) – der konvertierte 64‑Bit‑Wert (Long Integer).

### **Adapter**

Der Baustein besitzt zwei Adapter‑Schnittstellen:

*   **Socket AW_IN** – Unidirektionaler Eingangsadapter (Typ AW), der die Verbindung zu einem vorherigen Baustein herstellt, der WORD‑Daten liefert.
*   **Plug ALI_OUT** – Unidirektionaler Ausgangsadapter (Typ ALI), der die konvertierten LINT‑Daten an nachfolgende Bausteine weitergibt.

Beide Adapter sind unidirektional, d. h. sie übertragen Ereignisse und Daten nur in eine Richtung (Eingang → Ausgang).

## Funktionsweise

Der Ablauf innerhalb des Composite‑Bausteins ist streng sequentiell:

1.  Ein Ereignis **E1** am Socket **AW_IN** wird an den internen Funktionsbaustein **F_WORD_TO_LINT** (Instanzname *Convert*) weitergeleitet und aktiviert dessen **REQ‑Eingang**.
2.  Gleichzeitig wird der eingehende Datenwert **D1** (WORD) an den **IN‑Eingang** des Konverters gelegt.
3.  Der Konverter `F_WORD_TO_LINT` führt die Typumwandlung von WORD nach LINT durch und stellt das Ergebnis an seinem **OUT‑Ausgang** bereit.
4.  Nach Abschluss der Konvertierung erzeugt der Konverter ein **CNF‑Ereignis**, das an den **E1‑Eingang** des Ausgangsadapters **ALI_OUT** weitergegeben wird.
5.  Gleichzeitig wird der konvertierte Wert (LINT) vom **OUT‑Ausgang** des Konverters auf den Datenausgang **D1** des **ALI_OUT‑Adapters** gelegt.

Damit ist die Datenkonvertierung zu einem sicheren, ereignisgesteuerten Zeitpunkt abgeschlossen.

## Technische Besonderheiten

*   **Composite‑Baustein** – Die Konvertierungslogik ist vollständig in einem inneren Netzwerk gekapselt, das nur aus einem einzigen Konvertierungs‑FB besteht. Der Baustein besitzt keinen eigenen ECC‑Zustandsautomaten.
*   **Adapter‑basierte Schnittstelle** – Statt einzelner Ereignis‑/Daten‑Ein‑/Ausgänge werden Adapter verwendet. Dies ermöglicht eine modulare, wieder verwendbare Verbindung in Adapter‑basierten Steuerungsarchitekturen.
*   **Paket‑Struktur** – Der Baustein ist im Paket `adapter::conversion::unidirectional` abgelegt und verwendet den Konverter `iec61131::conversion::F_WORD_TO_LINT` aus der IEC‑61131‑Konvertierungsbibliothek.
*   **Unidirektionale Richtung** – Daten fließen nur vom Eingangsadapter zum Ausgangsadapter; Rückwärtskommunikation ist nicht vorgesehen.
*   **Lizenz** – Der Quellcode unterliegt der Eclipse Public License 2.0 (EPL‑2.0), entwickelt von der HR Agrartechnik GmbH.

## Zustandsübersicht

Da es sich um einen zusammengesetzten Baustein ohne eigenen Zustandsautomaten (ECC) handelt, gibt es keine definierten Zustände. Die Funktionalität wird vollständig durch den eingebetteten Funktionsbaustein `F_WORD_TO_LINT` gesteuert, der eine einmalige, ereignisgesteuerte Umwandlung durchführt. Der Baustein ist immer dann bereit, wenn ein Ereignis am Eingangsadapter eintrifft; nach der Konvertierung wartet er auf das nächste Ereignis.

## Anwendungsszenarien

*   **Datenkonvertierung in Adapterketten** – Wenn ein Steuerungssystem auf unidirektionalen Adaptern basiert und eine Komponente WORD‑Daten liefert, eine nachfolgende Komponente jedoch LINT‑Daten erwartet, kann AW_TO_ALI als Zwischenglied eingefügt werden.
*   **Anbindung von Feldgeräten mit unterschiedlichen Bitbreiten** – Z. B. die Integration eines Sensors, der 16‑Bit‑Messwerte (WORD) liefert, in eine Logik, die mit 64‑Bit‑Werten (LINT) arbeitet (etwa für hochauflösende Zähler oder Zeitstempel).
*   **Typanpassung in Bibliotheken** – Erweiterung einer bestehenden Adapterbibliothek um komfortable Konvertierungsbausteine, um die Kompatibilität zwischen verschiedenen Datenformaten zu gewährleisten.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eingang(sadapter) | Ausgang(sadapter) | Konvertierung | Besonderheiten |
|----------|-------------------|-------------------|---------------|----------------|
| **AW_TO_ALI** | AW (WORD) | ALI (LINT) | WORD → LINT | Unidirektional, Composite |
| `F_WORD_TO_LINT` (IEC 61131) | Einzelner REQ‑Eingang, IN (WORD) | Einzelner CNF‑Ausgang, OUT (LINT) | WORD → LINT | Standard‑FB, kein Adapter |
| `ALI_TO_AW` (hypothetisch) | ALI (LINT) | AW (WORD) | LINT → WORD | Umgekehrte Richtung |

Der Vorteil von AW_TO_ALI liegt in der nahtlosen Integration in adapterbasierte Systeme, während der reine IEC‑Baustein `F_WORD_TO_LINT` separat verdrahtet werden müsste. Bausteine mit Adapter‑Schnittstellen vereinfachen den Steuerungsentwurf, da sie standardisierte Stecker (Plugs/Sockets) bieten.

## Fazit

**AW_TO_ALI** ist ein kompakter, adapter‑basierter Konvertierungsbaustein für die Umwandlung von WORD‑ in LINT‑Daten. Durch die Nutzung des bewährten IEC‑61131‑Konverters `F_WORD_TO_LINT` und die Kapselung in eine Composite‑Struktur bietet er eine saubere, ereignisgesteuerte Schnittstelle für unidirektionale Adapteranwendungen. Der Baustein eignet sich besonders für den Einsatz in modularen Automatisierungssystemen, in denen Daten zwischen Komponenten mit unterschiedlichen Datenbreiten ausgetauscht werden müssen.