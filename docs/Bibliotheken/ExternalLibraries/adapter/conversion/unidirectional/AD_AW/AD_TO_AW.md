# AD_TO_AW


![AD_TO_AW](./AD_TO_AW.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AD_TO_AW** ist ein zusammengesetzter (Composite) FB, der einen DWORD-Adapter (Typ `AD`) in einen WORD-Adapter (Typ `AW`) umwandelt. Er kapselt die Konvertierung eines DWORD‑Wertes in einen WORD‑Wert und stellt die entsprechende Ereignis‑ und Datenweiterleitung bereit. Die Implementierung basiert auf einem internen Aufruf des Standard‑Konvertierungsbausteins `F_DWORD_TO_WORD` aus der IEC 61131‑Bibliothek.

## Schnittstellenstruktur
Der Baustein besitzt keine direkten Ein‑/Ausgangs‑Events oder Datenports. Alle Signale werden über die angeschlossenen Adapter (Socket und Plug) geführt.

### **Ereignis-Eingänge**
- **AD_IN.E1** (über Socket `AD_IN`): Dieses Ereignis triggert die Umwandlung des anliegenden DWORD‑Wertes.

### **Ereignis-Ausgänge**
- **AW_OUT.E1** (über Plug `AW_OUT`): Nach erfolgreicher Konvertierung wird dieses Ereignis gesendet.

### **Daten-Eingänge**
- **AD_IN.D1** (über Socket `AD_IN`): Eingangsdaten vom Typ `DWORD`, die in einen WORD‑Wert umgewandelt werden.

### **Daten-Ausgänge**
- **AW_OUT.D1** (über Plug `AW_OUT`): Ausgangsdaten vom Typ `WORD`, die das Ergebnis der Konvertierung enthalten.

### **Adapter**
| Rolle | Name  | Typ | Richtung | Kommentar |
|-------|-------|-----|----------|-----------|
| Socket | AD_IN | `adapter::types::unidirectional::AD` | Eingang (DWORD) | Liefert DWORD‑Daten und Ereignis. |
| Plug   | AW_OUT| `adapter::types::unidirectional::AW` | Ausgang (WORD) | Stellt WORD‑Daten und Ereignis bereit. |

Beide Adapter sind vom Typ *unidirectional*, d. h. die Kommunikation erfolgt in eine Richtung.

## Funktionsweise
1. Sobald am Socket `AD_IN` das Ereignis `E1` eintrifft, wird der Wert von `AD_IN.D1` (DWORD) an den internen Konvertierungsbaustein `F_DWORD_TO_WORD` übergeben.
2. Der interne Baustein führt die Konvertierung durch und legt das Ergebnis (WORD) an seinem Ausgang `OUT` an.
3. Der konvertierte Wert wird sofort an den Plug `AW_OUT.D1` weitergeleitet.
4. Gleichzeitig wird das Ereignis `E1` am Plug `AW_OUT` ausgelöst, um die nachgeschaltete Logik zu informieren.

Die gesamte Verarbeitung erfolgt ereignisgesteuert und synchron.

## Technische Besonderheiten
- **Kapselung**: Der FB verwendet die standardisierte IEC‑61131‑Funktion `F_DWORD_TO_WORD`, die eine saubere und portierbare Konvertierung gewährleistet.
- **Adapter‑basiert**: Ein‑ und Ausgänge sind ausschließlich über Adapter realisiert – es gibt keine separaten Event‑/Datenports auf Bausteinebene.
- **Unidirektionalität**: Die verwendeten Adapter unterstützen nur eine Datenflussrichtung, was die Handhabung in einfachen Konvertierungsketten erleichtert.
- **Composite‑Design**: Der FB besitzt kein eigenes ECC (Execution Control Chart); die Steuerung erfolgt vollständig durch den internen Baustein.

## Zustandsübersicht
Als zusammengesetzter Baustein ohne eigenes ECC besitzt **AD_TO_AW** keine internen Zustände. Die Ausführung ist rein ereignisgetrieben und erfolgt atomar bei jedem eingehenden Ereignis am Socket.

## Anwendungsszenarien
- **Adapter‑Anpassung**: Wenn ein Steuerungssystem Daten über einen DWORD‑Adapter bereitstellt, aber ein angeschlossenes Modul oder eine Komponente einen WORD‑Adapter erwartet.
- **Datenreduktion**: Gezieltes Abschneiden eines DWORD‑Wertes auf die unteren 16 Bit (WORD) für nachfolgende Verarbeitungsschritte.
- **Brückenbildung**: Einsatz in heterogenen Systemlandschaften, in denen unterschiedliche Adapter‑Typen aufeinander treffen.

## Vergleich mit ähnlichen Bausteinen
- **WORD_TO_DWORD**: Führt die entgegengesetzte Konvertierung (WORD → DWORD) durch und erweitert den Wert (in der Regel durch Nullen).
- **AD_TO_AD (z. B. AD_TO_AD mit anderen Typen)**: Andere Composite‑Bausteine können ähnliche Adapter‑Umwandlungen für weitere Datentypen (z. B. BYTE, INT, REAL) kapseln.
- **Direkte Nutzung von `F_DWORD_TO_WORD`**: Statt eines Composite‑Bausteins könnte die Konvertierungsfunktion direkt in ein FB‑Netzwerk eingebunden werden – der Composite bietet jedoch eine wiederverwendbare, gekapselte Lösung.

## Fazit
Der **AD_TO_AW**‑Funktionsblock ist ein einfacher, aber nützlicher Composite‑Baustein zur Umwandlung eines DWORD‑Adapters in einen WORD‑Adapter. Er nutzt eine standardisierte Konvertierungsfunktion, ist leicht verständlich und kann in vielen Adapter‑basierten Automatisierungssystemen eingesetzt werden. Durch die Kapselung in einem eigenen FB wird die Netzwerktopologie übersichtlicher und die Wiederverwendbarkeit erhöht.