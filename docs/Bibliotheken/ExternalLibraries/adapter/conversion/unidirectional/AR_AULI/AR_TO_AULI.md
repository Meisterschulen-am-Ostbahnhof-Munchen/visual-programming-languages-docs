# AR_TO_AULI


![AR_TO_AULI](./AR_TO_AULI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AR_TO_AULI** ist ein Composite-Baustein, der eine REAL-Eingangsadapter (AR) in eine ULINT-Ausgangsadapter (AULI) umwandelt. Er dient als unidirektionale Schnittstelle zwischen Komponenten, die mit dem Datentyp REAL arbeiten, und solchen, die ULINT (unsigned long integer) erwarten. Der Baustein kapselt die notwendige Konvertierung und stellt die Ereignis- und Datenweiterleitung automatisch sicher.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **AR_IN.E1** – Eingangsereignis vom AR-Adapter; löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **AULI_OUT.E1** – Ausgangsereignis an den AULI-Adapter; signalisiert, dass der konvertierte Wert bereitsteht.

### **Daten-Eingänge**
- **AR_IN.D1** – REAL-Wert aus dem AR-Adapter, der konvertiert werden soll.

### **Daten-Ausgänge**
- **AULI_OUT.D1** – ULINT-Wert, der aus dem REAL-Eingang konvertiert wurde.

### **Adapter**
- **AR_IN** (Socket) – Unidirektionaler AR-Adapter (Typ: adapter::types::unidirectional::AR) als Eingang.
- **AULI_OUT** (Plug) – Unidirektionaler AULI-Adapter (Typ: adapter::types::unidirectional::AULI) als Ausgang.

## Funktionsweise
Der Baustein ist als Composite FB realisiert und enthält intern einen einzigen Funktionsblock **F_REAL_TO_ULINT** aus der IEC‑61131‑Bibliothek. Die Arbeitsweise ist wie folgt:
1. Ein Ereignis am Socket **AR_IN.E1** löst die Ausführung des Konverters aus.
2. Der Datenwert **AR_IN.D1** wird an den Eingang **Convert.IN** weitergeleitet.
3. Der Konverter führt die Typumwandlung von REAL nach ULINT durch und stellt das Ergebnis am Ausgang **Convert.OUT** bereit.
4. Das Bestätigungsereignis **Convert.CNF** erzeugt ein Ereignis am Plug **AULI_OUT.E1**, das den angeschlossenen Baustein über den neuen Wert informiert.
5. Der konvertierte ULINT-Wert wird parallel auf **AULI_OUT.D1** ausgegeben.

Die Ereignis- und Datenverbindungen sind direkt und ohne zusätzliche Logik verdrahtet, sodass der Baustein eine reine Transformationshülle darstellt.

## Technische Besonderheiten
- **Unidirektionalität:** Sowohl der Eingangs- als auch der Ausgangsadapter sind unidirektional ausgelegt. Es erfolgt keine Rückmeldung oder Bestätigung vom Ausgang zum Eingang.
- **Verwendeter Konverter:** Der eingebettete FB **F_REAL_TO_ULINT** implementiert die standardisierte IEC‑61131‑Konvertierung. Rundungs- und Überlaufverhalten entsprechen den IEC‑Normvorgaben.
- **Ereignisgesteuerte Ausführung:** Die Konvertierung wird nur bei einem Ereignis am Eingang durchgeführt; ohne Ereignis bleibt der Ausgang unverändert.
- **Adapter‑Typen:** Die Adapter basieren auf einer unidirektionalen Variante, d. h. sie übertragen genau ein Ereignis und einen Datenwert pro Richtung.

## Zustandsübersicht
Als Composite FB besitzt **AR_TO_AULI** keine eigenen Zustände. Die interne Zustandslogik wird allein durch den eingebetteten **F_REAL_TO_ULINT** bestimmt, der in der Regel einen einfachen, ereignisgesteuerten Ablauf ohne Zustandsspeicherung realisiert (REQ → Verarbeitung → CNF). Der Baustein ist daher zustandslos und wartet nach jeder Konvertierung auf ein neues Eingangsereignis.

## Anwendungsszenarien
- **Schnittstellenanpassung:** Wenn eine Komponente (z. B. ein Regelalgorithmus) REAL‑Werte liefert, aber ein nachgeschaltetes Modul (z. B. eine Zähl- oder Indexlogik) ULINT‑Eingänge erwartet.
- **Adapter‑Bridge:** Verwendung in einer Tool‑Chain, die unterschiedliche Datentypen über Adapter verbindet, ohne dass der Entwickler die Konvertierung manuell vornehmen muss.
- **Datenintegration:** Einbinden von REAL‑basierten Sensoren oder Parametern in ein System, das intern mit ULINT arbeitet (z. B. für Status‑Codes oder kumulierte Werte).

## Vergleich mit ähnlichen Bausteinen
- **F_REAL_TO_ULINT** – Basisbaustein ohne Adapter; erfordert direkte Daten- und Ereignisverbindungen. **AR_TO_AULI** ist eine gekapselte Variante mit Adaptern, die die Einbindung in adapterbasierte Architekturen vereinfacht.
- **AR_TO_*‑Bausteine für andere Zieltypen** – Es existieren entsprechende Composite‑Bausteine für Konvertierungen von REAL nach LINT, DINT usw. Sie folgen dem gleichen Muster und nutzen jeweils den passenden IEC‑Konverter.
- **Direkte Konvertierung im Netzwerk** – Alternativ könnte man den F_REAL_TO_ULINT direkt in ein FB‑Netzwerk einbinden, was jedoch mehr manuelle Verdrahtung erfordert. **AR_TO_AULI** reduziert den Aufwand und verbessert die Wiederverwendbarkeit.

## Fazit
Der **AR_TO_AULI**‑Baustein ist eine einfache, aber nützliche Kapselung der REAL‑nach‑ULINT‑Konvertierung in einem adapterbasierten Format. Er erweitert die IEC‑61131‑Konvertierung um eine plug‑&‑play‑Schnittstelle für unidirektionale Adapter und ermöglicht eine saubere Trennung von Konvertierungslogik und Anwendungskommunikation. Der Baustein eignet sich besonders für modulare Systeme, die auf Adapterkonzepten aufbauen.