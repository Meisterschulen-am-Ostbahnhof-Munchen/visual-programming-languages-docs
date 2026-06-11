# AL_TO_AW


![AL_TO_AW](./AL_TO_AW.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AL_TO_AW ist ein zusammengesetzter (Composite) Baustein, der einen LWORD-Eingangsadaper vom Typ AL (unidirektional) in einen WORD-Ausgangsadaper vom Typ AW (unidirektional) umwandelt. Er kapselt die Konvertierungsfunktion und stellt eine einfache Schnittstelle für die Umwandlung von 64‑Bit‑Daten auf 16‑Bit‑Daten in der 4diac‑IDE bereit.

## Schnittstellenstruktur
Der Baustein besitzt keine diskreten Ereignis‑ oder Datenports, sondern ausschließlich Adapter‑Schnittstellen (Socket/Plug). Die nachfolgende Übersicht zeigt die verfügbaren Adapter:

### **Ereignis-Eingänge**
Keine separaten Ereignis-Eingänge. Das Ereignissignal wird über den AL_IN‑Adapter (Socket) geführt.

### **Ereignis-Ausgänge**
Keine separaten Ereignis-Ausgänge. Das Ereignissignal wird über den AW_OUT‑Adapter (Plug) ausgegeben.

### **Daten-Eingänge**
Keine separaten Daten-Eingänge. Die Daten werden über den AL_IN‑Adapter eingelesen.

### **Daten-Ausgänge**
Keine separaten Daten-Ausgänge. Die Daten werden über den AW_OUT‑Adapter ausgegeben.

### **Adapter**
- **AL_IN** (Socket) – Typ: `adapter::types::unidirectional::AL`  
  LWORD‑Eingangsadaper; enthält je ein Ereignis- und Datensignal (E1, D1).
- **AW_OUT** (Plug) – Typ: `adapter::types::unidirectional::AW`  
  WORD‑Ausgangsadaper; enthält je ein Ereignis- und Datensignal (E1, D1).

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
1. Ein Ereignis am Socket **AL_IN** (E1) triggert den internen Konvertierungs-FB `F_LWORD_TO_WORD`.
2. Gleichzeitig wird das LWORD‑Datum (D1) vom Eingangsadaper an den `IN`‑Eingang des Konvertierungs-FB weitergeleitet.
3. Der Konvertierungs-FB führt die Umwandlung von LWORD (64‑Bit) nach WORD (16‑Bit) durch.
4. Nach erfolgreicher Konvertierung wird ein Ereignis am `CNF`‑Ausgang des Konvertierungs-FB erzeugt, das an den Ausgangsadaper **AW_OUT** (E1) weitergegeben wird.
5. Das konvertierte WORD‑Datum (16 Bit) wird am `OUT`‑Ausgang des Konvertierungs-FB abgegriffen und an den Datenausgang des Adapters (D1) übergeben.

Die gesamte Logik besteht aus einer direkten Verbindungskette ohne Zwischenzustände oder Verzögerungen.

## Technische Besonderheiten
- **Verwendung standardisierter IEC 61131‑Konvertierung** – Intern wird der Baustein `F_LWORD_TO_WORD` aus der IEC 61131‑Bibliothek eingesetzt.
- **Adapterbasierte Schnittstelle** – Der Baustein ist vollständig in die Adapter‑Konzepte von 4diac eingebettet und kann einfach in bestehende Systeme mit unidirektionalen AL‑ und AW‑Adaptern integriert werden.
- **Keine Seiteneffekte** – Die Konvertierung erfolgt ohne Speicherung oder Zwischenpufferung; jedes eingehende Ereignis löst genau eine Ausgabe aus.
- **Kompatibilität** – Geeignet für Anwendungen, bei denen 64‑Bit‑LWORD‑Datensignale auf 16‑Bit‑WORD‑Signale reduziert werden müssen (z. B. bei der Anbindung älterer Steuerungen oder Feldbusse).

## Zustandsübersicht
Der Baustein besitzt keine internen Zustände. Es handelt sich um eine rein kombinatorische Transformation ohne sequentielle Logik oder Zustandsautomaten.

## Anwendungsszenarien
- **Protokollkonvertierung** – In Automatisierungssystemen, die unterschiedliche Datenwortbreiten verwenden (z. B. Umbau von 64‑Bit‑Messwerten auf 16‑Bit‑Ausgänge).
- **Schnittstellenanpassung** – Wenn ein System LWORD‑Daten liefert, aber ein nachgeschalteter Adapter nur WORD‑Daten verarbeitet.
- **Test‑ und Simulationsaufgaben** – Zum einfachen Umwandeln von Testdaten zwischen verschiedenen Adaptertypen.

## Vergleich mit ähnlichen Bausteinen
- **F_LWORD_TO_WORD** (direkter Funktionsblock) – Bietet die gleiche Konvertierung, jedoch ohne Adapter‑Kapselung. AL_TO_AW integriert diese Konvertierung direkt in eine adapterbasierte Umgebung.
- **Andere Adapter‑Konvertierungen** – Es existieren ähnliche Bausteine für andere Datentyp‑Paare (z. B. DWORD_TO_WORD). AL_TO_AW ist speziell für die Kombination LWORD↔WORD ausgelegt.
- **Selbst erstellte Composite‑Bausteine** – Der Baustein zeigt, wie man durch Kapselung wiederkehrende Konvertierungsaufgaben effizient in der 4diac‑IDE abbildet.

## Fazit
AL_TO_AW ist ein kompakter und klar strukturierter Composite‑Funktionsblock zur Umwandlung eines LWORD‑Adapters in einen WORD‑Adapter. Er nutzt die bewährte IEC‑Konvertierungsfunktion, bietet eine adapterkonforme Schnittstelle und eignet sich hervorragend für die Integration in 4diac‑Projekte, die eine saubere Trennung von Datenwortbreiten erfordern.