# BYPASS_AX_AX


![BYPASS_AX_AX](./BYPASS_AX_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **BYPASS_AX_AX** dient zur Weiterleitung und parallelen Bypass-Verarbeitung von AX‑Signalen. Er kombiniert einen direkten Durchgang vom Eingang **IN** zum Ausgang **OUT** mit einer booleschen Oder‑Verknüpfung der eingehenden Daten, die über ein flankengesteuertes D‑Flipflop auf den Bypass‑Ausgang **BY_OUT** gegeben wird.

## Schnittstellenstruktur
### **Ereignis‑Eingänge**
- **IN.E1** – Ereignis des Signal‑Eingangs  
- **BY_IN.E1** – Ereignis des Bypass‑Eingangs

### **Ereignis‑Ausgänge**
- **OUT.E1** – Ereignis des Signal‑Ausgangs  
- **BY_OUT.E1** – Ereignis des Bypass‑Ausgangs

### **Daten‑Eingänge**
- **IN.D1** – Datenwert des Signal‑Eingangs (Typ abhängig vom verwendeten AX‑Adapter)  
- **BY_IN.D1** – Datenwert des Bypass‑Eingangs (gleicher Typ)

### **Daten‑Ausgänge**
- **OUT.D1** – Datenwert des Signal‑Ausgangs (identisch mit IN.D1)  
- **BY_OUT.D1** – Datenwert des Bypass‑Ausgangs (Ergebnis der Oder‑Verknüpfung, gespeichert im Flipflop)

### **Adapter**
Der FB verwendet vier Adapter vom Typ `adapter::types::unidirectional::AX`:
- **IN** (Socket) – Signal‑Eingang  
- **BY_IN** (Socket) – Bypass‑Eingang  
- **OUT** (Plug) – Signal‑Ausgang  
- **BY_OUT** (Plug) – Bypass‑Ausgang

Jeder AX‑Adapter überträgt ein Ereignis‑/Daten‑Paar (E1/D1) in einer Richtung.

## Funktionsweise
Der FB realisiert zwei parallele Pfade:

1. **Direkter Pfad:**  
   Ein Ereignis auf **IN.E1** wird direkt an **OUT.E1** weitergegeben, ebenso der zugehörige Datenwert **IN.D1** an **OUT.D1**. Dies stellt eine 1:1‑Durchschaltung des Signals dar.

2. **Bypass‑Pfad:**  
   Sowohl ein Ereignis auf **IN.E1** als auch auf **BY_IN.E1** lösen die Verarbeitung im Baustein `OR_2_BOOL` aus. Dieser verknüpft die Datenwerte **IN.D1** und **BY_IN.D1** boolesch – es handelt sich um eine logische Oder‑Verknüpfung der beiden binären Eingänge.  
   Das Ergebnis der Verknüpfung wird an den Dateneingang **D** des D‑Flipflops (`E_D_FF`) gelegt. Der Takt des Flipflops wird durch das Rücksignal `OR_2_BOOL.CNF` ausgelöst, also nach Abschluss der Oder‑Berechnung.  
   Der Ausgang **Q** des Flipflops wird auf **BY_OUT.D1** gelegt, und das zugehörige Ereignis **BY_OUT.E1** wird durch den Flipflop‑Ausgang **EO** angesteuert.

## Technische Besonderheiten
- **Boolesche Oder‑Verknüpfung:** Die Daten werden nicht etwa addiert oder gemischt, sondern logisch OR‑verknüpft. Daher sind die Datenwerte als boolesch (TRUE/FALSE) anzusehen.
- **Flankengesteuertes Flipflop:** Der Bypass‑Wert wird immer dann aktualisiert, wenn mindestens einer der beiden Eingänge (IN oder BY_IN) ein Ereignis liefert. Das Flipflop speichert den letzten berechneten OR‑Wert.
- **Unabhängige Ereignisweitergabe:** Der direkte Pfad ist asynchron – jedes Ereignis auf IN wird sofort an OUT weitergegeben, ohne auf den Bypass‑Pfad zu warten.

## Zustandsübersicht
Der FB selbst besitzt keinen eigenen Zustandsautomaten, jedoch wird durch das interne D‑Flipflop ein binärer Zustand realisiert:
- **Zustand 0:** Flipflop‑Ausgang Q = FALSE → BY_OUT.D1 = FALSE  
- **Zustand 1:** Flipflop‑Ausgang Q = TRUE → BY_OUT.D1 = TRUE

Der Zustand wechselt bei jeder positiven Flanke des Taktes (`OR_2_BOOL.CNF`) auf den aktuellen D‑Wert. Der Anfangszustand ist nicht definiert und muss ggf. extern initialisiert werden.

## Anwendungsszenarien
- **Bypass‑Schaltung in Steuerungen:** Ein Normalsignal (IN → OUT) soll unverändert durchgeschleift werden, gleichzeitig wird eine Oder‑Verknüpfung von Normalsignal und einem zusätzlichen Bypass‑Signal für Überwachungszwecke erzeugt.
- **Not‑Aktivierung:** Der Bypass‑Eingang kann als manuelle Übersteuerung (z. B. „Handbetrieb“) verwendet werden, während der automatische Betrieb am Hauptausgang weiterläuft.
- **Logische Signalverfolgung:** Durch die getrennten Ausgänge können sowohl das Originalsignal als auch die verknüpfte Logik parallel ausgewertet werden.

## Vergleich mit ähnlichen Bausteinen
- **Einfacher Durchgangs‑FB (z. B. MOVE_AX):** Leitet das Signal 1:1 weiter, erzeugt aber keinen Bypass‑Ausgang. BYPASS_AX_AX bietet zusätzlich die Verknüpfungslogik und einen zweiten Ausgang.
- **OR‑Baustein ohne Flipflop:** Ein reines Oder würde den Bypass‑Ausgang kontinuierlich aktualisieren, ohne Zwischenspeicherung. Der integrierte Flipflop sorgt für eine flankengesteuerte Aktualisierung, die bei zyklischen Steuerungen oder zeitlich entkoppelten Ereignissen von Vorteil ist.
- **Adapter‑basierte Lösung mit zwei separaten FBs:** Man könnte einen OR‑FB und einen Flipflop‑FB separat verdrahten – BYPASS_AX_AX kapselt diese Funktionalität in einem kompakten Baustein, reduziert die Anzahl der Verbindungen und vereinfacht die Handhabung.

## Fazit
Der **BYPASS_AX_AX** ist ein nützlicher Funktionsblock für Anwendungen, die sowohl eine direkte Signalweiterleitung als auch eine logische Oder‑Verknüpfung mit gespeichertem Ausgang erfordern. Durch die Kombination von Durchgangs‑ und Bypass‑Pfad in einem Baustein wird die Netzwerkstruktur übersichtlich gehalten. Die Verwendung von unidirektionalen AX‑Adaptern macht ihn kompatibel mit typischen Industriekommunikationsprotokollen auf Basis des IEC 61499‑Standards.