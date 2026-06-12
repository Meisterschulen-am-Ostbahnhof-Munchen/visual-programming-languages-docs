# AUI_AX_SEL_REQ


![AUI_AX_SEL_REQ](./AUI_AX_SEL_REQ.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUI_AX_SEL_REQ** ist ein binärer Selektorbaustein, der über einen Ereigniseingang (REQ) gesteuert wird. Er wählt basierend auf einem über einen **Adapter** (G) bereitgestellten Auswahlkriterium zwischen zwei Eingangswerten (IN0, IN1) aus und gibt das Ergebnis am Ausgang OUT aus. Der Baustein dient als kompakte, wiederverwendbare Komponente für die Signalselektion in Automatisierungsanwendungen und erweitert die Funktionalität eines einfachen Umschalters um eine ereignisgesteuerte Ausführung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Dient als Auslöser für den Selektionsvorgang. Der Wert des Adapters G wird ausgelesen, die Auswahl getroffen und das Ergebnis am Ausgang bereitgestellt. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Wird ausgelöst, sobald der Selektionsvorgang abgeschlossen ist und der Ausgang OUT einen gültigen Wert enthält. |

### **Daten-Eingänge**

| Eingang | Datentyp | Beschreibung |
|---------|----------|--------------|
| IN0     | UINT     | Erster wählbarer Eingangswert. |
| IN1     | UINT     | Zweiter wählbarer Eingangswert. |

### **Daten-Ausgänge**

| Ausgang | Datentyp | Beschreibung |
|---------|----------|--------------|
| OUT     | UINT     | Ausgewählter Wert – entweder IN0 oder IN1, abhängig vom über den Adapter G gelieferten Selektorkriterium. |

### **Adapter**

| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| G       | adapter::types::unidirectional::AX | Bidirektionaler Adapter, der das Selektorkriterium (z. B. ein boolesches Signal) sowie ein zugehöriges Ereignis (E1, D1) bereitstellt. Der Wert von D1 entscheidet, welcher Eingang (IN0 bei D1 = 0, IN1 bei D1 = 1) an OUT durchgeschaltet wird. |

## Funktionsweise

Der Baustein realisiert die Auswahl über einen internen Funktionsblock **F_SEL** (Typ: `iec61131::selection::F_SEL`). Die Ereignisverkettung arbeitet wie folgt:

1. Ein **REQ**-Ereignis am Eingang oder ein Ereignis vom **Adapter G (E1)** wird zum internen **F_SEL.REQ** weitergeleitet.
2. Der über den Adapter an **G.D1** anliegende Wert wird an den Selektoreingang **F_SEL.G** übergeben.
3. Die Datenwerte **IN0** und **IN1** werden direkt an die entsprechenden Eingänge von **F_SEL** weitergegeben.
4. Der interne Baustein führt die binäre Selektion aus: Ist **G.D1 = 0** wird **IN0**, andernfalls **IN1** an **F_SEL.OUT** ausgegeben.
5. Das Ergebnis wandert zu **OUT** und das Ereignis **F_SEL.CNF** löst den Ausgang **CNF** aus.

Somit wird die Selektion entweder durch ein externes REQ-Ereignis oder durch ein vom Adapter kommendes Ereignis (E1) angestoßen. Der Ausgang OUT bleibt nach der Ausführung bis zum nächsten Selektionsvorgang erhalten.

## Technische Besonderheiten

* **Adapterbasierte Selektion:** Die Verwendung des Adapters G (Typ AX) ermöglicht eine flexible Kopplung mit anderen Bausteinen oder Hardware-Schnittstellen, die ein einheitliches Selektionssignal liefern.
* **Ereignisgesteuert:** Sowohl das externe REQ-Ereignis als auch das Ereignis vom Adapter können den Vorgang auslösen. Dies erlaubt sowohl zyklisches als auch ereignisorientiertes Abfragen.
* **Typsicherheit:** Die Eingänge sind als UINT (unsigned integer) definiert; der Baustein arbeitet ausschließlich mit diesem Datentyp.

## Zustandsübersicht

Der Baustein ist rein funktional und besitzt keinen eigenen endlichen Automaten. Die interne Logik wird vollständig vom enthaltenen **F_SEL**-Baustein abgedeckt, der einen kombinatorischen Selektionsvorgang ereignisgesteuert ausführt. Nach Auslösung von REQ oder Adapter-E1 wird der Ausgang OUT diskret gesetzt; es gibt keine internen Zustände oder Verzögerungen.

## Anwendungsszenarien

* **Konfigurierbare Signalauswahl:** In Maschinensteuerungen, bei denen zwischen zwei Sensoren oder Messwerten (z. B. Geschwindigkeit, Druck) umgeschaltet werden muss, abhängig von einem Steuersignal.
* **Parametrierbare Betriebsmodi:** Auswahl zwischen zwei Parametersätzen (z. B. IN0 = Normalbetrieb, IN1 = Testmodus) über ein zentrales Selektorsignal.
* **Fehlerersatzwertschaltung:** Falls ein Primärwert (IN0) ungültig ist, kann über den Adapter der Ersatzwert (IN1) aktiviert werden.
* **Adaptervermittelte Steuerung:** Anbindung an übergeordnete Systeme, die über einen AX-Adapter ein Selektionskriterium senden (z. B. ein digitaler Ausgang einer SPS).

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum standardmäßigen **F_SEL** (IEC 61131-3) bietet **AUI_AX_SEL_REQ** eine ereignisgesteuerte Kapselung mit Adapteranbindung. Während F_SEL in reinen Funktionsbausteinsprachen ohne Ereignisse arbeitet, ist AUI_AX_SEL_REQ speziell für den ereignisorientierten Ablauf in 61499-Systemen optimiert. Gegenüber einem **MUX-Baustein** (Multiplexer mit mehr als zwei Eingängen) beschränkt sich dieser Baustein auf zwei Wahlmöglichkeiten und nutzt einen dedizierten Adapter statt eines zusätzlichen Dateneingangs für die Selektion.

## Fazit

Der **AUI_AX_SEL_REQ** bietet eine elegante und standardisierte Möglichkeit, eine binäre Auswahl in 61499-basierten Automatisierungssystemen zu realisieren. Durch die Integration eines Adapters bleibt die Schnittstelle flexibel, und die ereignisgesteuerte Ausführung gewährleistet eine deterministische Verarbeitung. Er eignet sich besonders für Anwendungen, bei denen das Selektionskriterium nicht als direktes Datensignal, sondern über eine gerichtete Kommunikation (Adapter) bereitgestellt wird.