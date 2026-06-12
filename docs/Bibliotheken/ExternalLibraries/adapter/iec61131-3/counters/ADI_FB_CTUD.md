# ADI_FB_CTUD


![ADI_FB_CTUD](./ADI_FB_CTUD.svg)

* * * * * * * * * *
## Einleitung
Der **ADI_FB_CTUD** ist ein aufwärts/abwärts zählender Funktionsbaustein für ganzzahlige Werte (DINT). Er realisiert einen Vorwärts-/Rückwärtszähler, der über standardisierte **Adapterschnittstellen** gesteuert wird. Der Baustein kapselt die IEC-61131-3-Komponente `FB_CTUD_DINT` und stellt deren Funktionalität über ereignisgesteuerte Adapter bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine direkten Ereigniseingänge. Die Ansteuerung erfolgt ausschließlich über die **Sockets**:
- **CU (Count Up)** – Ereignis zum Inkrementieren des Zählwerts
- **CD (Count Down)** – Ereignis zum Dekrementieren des Zählwerts
- **R (Reset)** – Ereignis zum Zurücksetzen des Zählwerts auf Null
- **LD (Load)** – Ereignis zum Laden des Presetwerts
- **PV (Preset Value)** – Ereignis zum Setzen des Presetwerts (Datenwert)

Diese Adapter liefern sowohl ein Ereignis als auch einen Datenwert (bei AX-Adapter über den Datenausgang `D1`).

### **Ereignis-Ausgänge**
- **CNF** – Bestätigungsereignis, das nach jeder Verarbeitung eines der Eingangsereignisse ausgegeben wird.

### **Daten-Eingänge**
Die Datenwerte der Eingangsadapter werden über die Verbindungen des internen FB `FB_CTUD_DINT` verarbeitet. Die Adapter liefern folgende Daten:
- **CU.D1** – Zählrichtung (Bool, 1 = Aufwärtszählen)
- **CD.D1** – Zählrichtung (Bool, 1 = Abwärtszählen)  
  (Hinweis: Im Standard-CTUD-DINT wird üblicherweise nur ein Zählereignis mit Richtungsauswahl verwendet; hier werden CU/CD als separate Ereignisse behandelt.)
- **R.D1** – Reset-Signal (Bool)
- **LD.D1** – Load-Signal (Bool)
- **PV.D1** – Presetwert (DINT)

### **Daten-Ausgänge**
Die Ausgangsdaten werden über die Plug-Adapter bereitgestellt:
- **QU.D1** – Zähler hat aufwärtsgeschaltet (Bool, nach CU-Ereignis)
- **QD.D1** – Zähler hat abwärtsgeschaltet (Bool, nach CD-Ereignis)
- **CV.D1** – Aktueller Zählwert (DINT)

### **Adapter**
Der Baustein verwendet drei verschiedene Adaptertypen:
- **unidirectional::AX** – für Ereignis- und Bool-Daten (CU, CD, R, LD als Sockets; QU, QD als Plugs)
- **unidirectional::ADI** – für Wertübergabe (PV als Socket, CV als Plug)

Die Adapter sind so konzipiert, dass sie sowohl das Ereignis als auch den zugehörigen Datenwert in einem Zug übertragen.

## Funktionsweise
Der interne FB `FB_CTUD_DINT` realisiert die klassische Aufwärts-/Abwärtszählerlogik:
- Bei einem Ereignis auf **CU** wird der Zählwert um 1 erhöht, sofern `CU.D1` = TRUE (oder das Ereignis allein als Aufwärtsimpuls gilt).
- Bei einem Ereignis auf **CD** wird der Zählwert um 1 verringert, sofern `CD.D1` = TRUE.
- Ein Ereignis auf **R** setzt den Zählwert auf 0 zurück.
- Ein Ereignis auf **LD** lädt den aktuellen Zählwert mit dem über **PV** übergebenen Wert.
- Nach jeder Verarbeitung wird **CNF** ausgegeben, sowie die Ereignisse **QU.E1** und **QD.E1** über die entsprechenden Adapter, wenn sich der Zählwert geändert hat.

**Wichtig:** Der Baustein feuert die Ausgangsereignisse (QU.E1, QD.E1) bei *jedem* Update (CU, CD, R, LD, PV) – nicht nur bei einer tatsächlichen Wertänderung. Soll eine reine Flankenauswertung (on-change) erfolgen, wird der Einsatz eines **AX_D_FF** als Filter empfohlen.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle:** Alle Ein- und Ausgänge erfolgen über standardisierte unidirektionale Adapter, was die Wiederverwendbarkeit und Kapselung erhöht.
- **IEC-61131-3-Kompatibilität:** Der interne Zähler entspricht der Norm und erlaubt einfache Migration zwischen verschiedenen Steuerungssystemen.
- **Immer aktive Ereignisse:** Wie oben beschrieben, werden Ausgangsereignisse bei jedem Eingangsereignis generiert – dies kann in zeitkritischen Anwendungen zu hoher Buslast führen.
- **Kein Zustandsautomat auf oberster Ebene:** Der FB besitzt kein eigenes ECC; die gesamte Logik wird durch den internen FB ausgeführt.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten. Die Verarbeitung erfolgt strikt ereignisgesteuert:
1. Warten auf ein Ereignis an einem der Sockets.
2. Verarbeitung des zugehörigen Datenwerts (sofern vorhanden) und des internen Zählerzustands.
3. Ausgabe von **CNF** sowie ggf. **QU.E1** und **QD.E1**.
4. Zurück zu Schritt 1.

## Anwendungsszenarien
- **Zählen von Impulsen** in Fertigungsanlagen (z. B. Werkstückzähler).
- **Positionserfassung** mit Inkrementalgebern (Auf-/Abwärtszählung).
- **Stücklisten- und Bestandszählung** mit Rückstellmöglichkeit.
- **Ereignisgesteuerte Steuerungen** in der Automatisierungstechnik, bei denen Zählerstände über Adapter ausgetauscht werden.

## Vergleich mit ähnlichen Bausteinen
| Eigenschaft | ADI_FB_CTUD | Standard CTUD (IEC 61131-3) |
|-------------|--------------|------------------------------|
| Schnittstelle | Adapter-basiert (AX/ADI) | Direkte Ein-/Ausgänge (Events, Daten) |
| Ereignisverhalten | Ausgang bei jedem Update | Meist Flanken- oder wertabhängig |
| Wiederverwendbarkeit | Leicht durch Adapter-Kapselung | Abhängig von der konkreten Steuerung |
| Kompatibilität | IEC-61131-3-konform (intern) | Direkte Normimplementierung |
| Filterung | Empfehlung: AX_D_FF | Teilweise integriert |

Der ADI_FB_CTUD bietet eine saubere adapterbasierte Kapselung, erfordert jedoch bei Bedarf nach on-change-Triggering zusätzliche Maßnahmen.

## Fazit
Der **ADI_FB_CTUD** ist ein flexibler und normenkonformer Aufwärts-/Abwärtszähler mit DINT-Wertebereich, der sich durch seine moderne Adapterschnittstelle auszeichnet. Er eignet sich besonders für modulare Steuerungsarchitekturen, in denen Komponenten über standardisierte Adapter kommunizieren. Die Besonderheit des immer aktiven Ereignisausgangs sollte bei der Integration in Echtzeitsysteme berücksichtigt werden.