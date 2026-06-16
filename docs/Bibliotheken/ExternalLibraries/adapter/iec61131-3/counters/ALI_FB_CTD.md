# ALI_FB_CTD


![ALI_FB_CTD](./ALI_FB_CTD.svg)

* * * * * * * * * *
## Einleitung

Der **ALI_FB_CTD** ist ein Abwärtszähler (Down Counter) für LINT-Werte (64‑Bit Integer) mit Adapter‑Schnittstellen nach IEC 61499. Er ist speziell für die Verwendung mit den unidirektionalen Adaptern `AX` (Ereignis‑/Bool‑Träger) und `ALI` (LINT‑Wert‑Träger) ausgelegt. Der Baustein kapselt den Standard‑FB `FB_CTD_LINT` aus der Bibliothek `iec61131::counters` und erweitert ihn um eine adapterbasierte Anbindung, die eine lose Kopplung zwischen den Funktionsbausteinen ermöglicht.

Der Baustein feuert seine Ereignisausgänge bei jeder Aktualisierung – unabhängig davon, ob sich der Zählerwert tatsächlich ändert. Für eine änderungsgetriggerte Weiterverarbeitung wird empfohlen, einen `AX_D_FF` als Filter vorzuschalten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine – alle Ereignis‑ und Dateninformationen werden über Adapter‑Sockets (CD, LD, PV) übertragen.

### **Ereignis-Ausgänge**
- **CNF** (Event): Bestätigung der ausgeführten Operation (wird nach jeder Aktualisierung gesendet).

### **Daten-Eingänge**
Es existieren keine separaten DataInputs. Die Eingabedaten werden über die folgenden Adapter‑Sockets bereitgestellt:
- **CD** (Socket, Typ `adapter::types::unidirectional::AX`): Abwärtszählimpuls (aktiviert den Zählvorgang).
- **LD** (Socket, Typ `adapter::types::unidirectional::AX`): Ladeimpuls (aktiviert das Laden des Preset‑Werts).
- **PV** (Socket, Typ `adapter::types::unidirectional::ALI`): Preset‑Wert (LINT); der Wert wird beim Laden (LD) übernommen.

### **Daten-Ausgänge**
Es existieren keine separaten DataOutputs. Die Ausgabedaten werden über die folgenden Adapter‑Plugs bereitgestellt:
- **Q** (Plug, Typ `adapter::types::unidirectional::AX`): Ausgangssignal (Bool) – zeigt an, ob der Zählerstand **Null** erreicht hat.
- **CV** (Plug, Typ `adapter::types::unidirectional::ALI`): Aktueller Zählerwert (LINT).

### **Adapter**

| Bezeichnung | Richtung | Typ | Beschreibung |
|-------------|----------|-----|--------------|
| CD          | Socket   | AX  | Abwärtszählimpuls (Ereignis + Bool) |
| LD          | Socket   | AX  | Ladeimpuls (Ereignis + Bool) |
| PV          | Socket   | ALI | Preset‑Wert (LINT) |
| Q           | Plug     | AX  | Ausgangssignal bei Zählerstand = 0 |
| CV          | Plug     | ALI | Aktueller Zählerwert (LINT) |

## Funktionsweise

Der ALI_FB_CTD realisiert einen Abwärtszähler mit Laden. Die interne Logik wird durch den FB `FB_CTD_LINT` abgebildet:

1. **Laden (Load)**  
   Ein Ereignis am Socket **LD** (über `LD.E1`) überträgt den Datenwert von **PV** (über `PV.D1`) in den internen Zähler. Der Zählerstand wird auf den Preset‑Wert gesetzt.

2. **Abwärtszählen (Count Down)**  
   Ein Ereignis am Socket **CD** (über `CD.E1`) dekrementiert den aktuellen Zählerstand um 1, sofern er größer als 0 ist.

3. **Ausgangssignalisierung**  
   - Der aktuelle Zählerwert wird stets über den Plug **CV** ausgegeben (als LINT).  
   - Der Plug **Q** liefert `true`, wenn der Zählerstand **Null** erreicht hat (Bool‑Wert über den AX‑Adapter).  
   - Das Ereignis **CNF** wird nach **jeder** Verarbeitung (sowohl nach CD, LD als auch PV) gesendet.

4. **Ereignisweitergabe**  
   Die eingehenden Ereignisse von CD, LD und PV werden alle auf den **REQ**‑Eingang des internen FB vereinigt. Dessen **CNF**‑Ausgang wird dann auf die Ausgangsadapter (Q.E1, CV.E1) und auf den externen Ereignisausgang CNF verteilt.

## Technische Besonderheiten

- **Immer‑Auslösen**: Der Baustein sendet die Ausgangsereignisse (Q.E1, CV.E1, CNF) bei **jeder** Aktualisierung – auch wenn sich der Zählerwert nicht ändert (z.B. bei wiederholtem CD auf 0). Für eine änderungsbasierte Auslösung muss ein `AX_D_FF` (Flanken‑Detektor) zwischengeschaltet werden.
- **Adapter‑Kopplung**: Die Verwendung von unidirektionalen Adaptern (AX, ALI) ermöglicht eine flexible Verschaltung in IEC‑61499‑Netzwerken, ohne starre Daten‑ und Ereignisverbindungen.
- **LINT‑Werte**: Der Zähler arbeitet mit 64‑Bit‑Integer, geeignet für große Zählbereiche.
- **Interne Struktur**: Der Baustein delegiert die gesamte Zähllogik an den erprobten Standard‑FB `FB_CTD_LINT` der Bibliothek `iec61131::counters`.

## Zustandsübersicht

Der ALI_FB_CTD besitzt **keinen expliziten Zustandsautomaten** im FB‑Netzwerk. Sein Verhalten ist rein ereignisgesteuert und kombinatorisch:

| Eingangsereignis | Aktion |
|------------------|--------|
| LD aktiviert | Zählerstand = Preset‑Wert |
| CD aktiviert | Zählerstand dekrementieren (falls > 0) |
| PV aktiviert | Keine Zähleränderung, aber Ereignis CNF wird gesendet. Der Datenwert von PV wird nicht unmittelbar übernommen – ein LD ist erforderlich. |

Der aktuelle Zählerstand und der Bool‑Ausgang werden nach jedem Schritt aktualisiert.

## Anwendungsszenarien

- **Stückzähler in der Fertigung**: Am Ende eines Produktionsschritts wird ein Impuls auf CD gegeben; der Zähler zählt von einer vorgegebenen Stückzahl (PV) abwärts. Bei Null wird Q aktiv und signalisiert z.B. „Batch fertig“.
- **Zeitsteuerung mit Pulszählung**: Ein Taktgeber liefert Impulse auf CD; nach einer vordefinierten Anzahl (PV) wird ein Ereignis ausgelöst.
- **Wartungsintervall**: Der Zähler dient als Count‑Down in Wartungszyklen; nach Erreichen von 0 wird ein Alarm ausgelöst.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Besonderheit |
|----------|--------------|
| **ALI_FB_CTD** (dieser Baustein) | Verwendet AX‑ und ALI‑Adapter; immer‑auslösend; geeignet für adapterbasierte Architekturen. |
| **FB_CTD_LINT** (Standard) | Reiner Daten‑/Ereignis‑FB ohne Adapter; Ereignisauslösung direkt über die Schnittstellen. |
| **CTU** (Aufwärtszähler) | Zählt aufwärts, anstatt abwärts; andere Anwendungslogik. |
| **Zählbausteine mit Flankenunterdrückung** | Sie besitzen eigene Filterlogik (z.B. AX_D_FF) und lösen nur bei tatsächlichen Wertänderungen aus. |

Der ALI_FB_CTD eignet sich besonders in Umgebungen, die auf Adaptern basieren und bei denen ein einfaches, zuverlässiges Abwärtszählen ohne zusätzliche Filter gewünscht ist.

## Fazit

Der **ALI_FB_CTD** ist ein robuster Abwärtszähler für LINT‑Werte, der speziell für die Adapter‑Technik in IEC‑61499‑Systemen entwickelt wurde. Er bietet eine klare, auf Adaptern basierende Schnittstelle und ist dank der internen Nutzung von `FB_CTD_LINT` zuverlässig und getestet. Durch seine „Immer‑Auslösen“‑Eigenschaft eignet er sich für Anwendungen, bei denen jede Zustandsänderung am Eingang sofort weitergeleitet werden soll. Wo eine änderungsbasierte Auslösung erforderlich ist, kann ein einfacher Filterbaustein ergänzt werden. Insgesamt stellt er eine wertvolle Ergänzung für adapterorientierte Automatisierungslösungen dar.