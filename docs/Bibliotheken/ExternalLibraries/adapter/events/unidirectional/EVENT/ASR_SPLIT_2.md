# ASR_SPLIT_2


![ASR_SPLIT_2](./ASR_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ASR_SPLIT_2** dient der Aufteilung eines eingehenden unidirektionalen ASR-Adapters (Application Service Request) auf zwei identische Ausgangsadapter. Er ist als generischer Baustein konzipiert und ermöglicht es, ein ASR-Signal an zwei separate Verbraucher oder nachfolgende Bausteine weiterzuleiten, ohne die Logik zu verändern.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Typ | Richtung | Name | Beschreibung |
|-----|----------|------|--------------|
| `adapter::types::unidirectional::ASR` | Eingang (Socket) | **IN** | Eingehendes ASR-Signal |
| `adapter::types::unidirectional::ASR` | Ausgang (Plug) | **OUT1** | Erster ausgehender ASR-Pfad |
| `adapter::types::unidirectional::ASR` | Ausgang (Plug) | **OUT2** | Zweiter ausgehender ASR-Pfad |

## Funktionsweise
Der Baustein leitet das über den Socket **IN** eingehende ASR-Signal unverändert an beide Plugs **OUT1** und **OUT2** weiter. Es erfolgt keine Verarbeitung, Filterung oder Verzögerung – das Signal wird rein passiv auf zwei Pfade verzweigt. Jeder Ausgang stellt die exakt gleiche Information wie der Eingang bereit.

## Technische Besonderheiten
- Der Baustein ist als **Generischer Funktionsblock (Generic FB)** implementiert. Die tatsächliche Typinstanz wird zur Laufzeit durch die Konfiguration des generischen Klassenattributs (`eclipse4diac::core::GenericClassName = 'GEN_ASR_SPLIT'`) festgelegt.
- Es werden keinerlei Ereignis- oder Daten-Eingänge/Ausgänge genutzt – die gesamte Kommunikation erfolgt ausschließlich über die Adapter-Schnittstellen.
- Die Ausgänge sind voneinander unabhängig; ein Fehler oder eine Blockade an einem Ausgang beeinflusst den anderen nicht.

## Zustandsübersicht
Der Baustein besitzt kein eigenes Zustandsdiagramm, da er rein passiv arbeitet. Sein Verhalten entspricht einer statischen Verzweigung.

## Anwendungsszenarien
- **Parallelisierung von Dienstanfragen:** Ein ASR (z. B. eine Anforderung eines Services) soll an zwei unabhängige Komponenten gesendet werden, z. B. an eine Logging-Komponente und gleichzeitig an einen Ausführungsdienst.
- **Redundanz:** Verteilung eines Signals auf zwei redundante Pfade zur Erhöhung der Ausfallsicherheit.
- **Adapter‑Brücke:** Einsatz in Systemen, bei denen eine ASR‑Verbindung auf zwei Adapter‑Punkte aufgeteilt werden muss, ohne die Logik zu kopieren.

## Vergleich mit ähnlichen Bausteinen
- **ASR_MERGE_2** (hypothetisch): Führt zwei ASR‑Eingänge zu einem Ausgang zusammen (z. B. mittels Priorität oder logischer ODER‑Verknüpfung). Der **ASR_SPLIT_2** macht das Gegenteil.
- **SPLIT_1_to_N** (generische Split-Komponenten): Ein allgemeiner Splitter, der mit einer konfigurierbaren Anzahl von Ausgängen arbeitet. Der **ASR_SPLIT_2** ist eine spezialisierte Version mit fest zwei Ausgängen.

## Fazit
Der **ASR_SPLIT_2** ist ein einfacher, aber nützlicher generischer Baustein zur Vervielfachung von ASR-Signalen. Durch die Verwendung von plattformunabhängigen Adaptern und die rein passive Funktionsweise eignet er sich für alle Szenarien, in denen ein Dienstsignal auf mehrere Pfade verteilt werden muss. Seine Integration erfolgt ohne Konfigurationsaufwand und ohne Seiteneffekte auf die übertragenen Daten.