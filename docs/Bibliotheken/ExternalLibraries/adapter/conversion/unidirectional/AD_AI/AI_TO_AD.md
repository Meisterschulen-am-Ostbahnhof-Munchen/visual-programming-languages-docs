# AI_TO_AD


![AI_TO_AD](./AI_TO_AD.svg)

* * * * * * * * * *
## Einleitung
Der Composite-Funktionsbaustein **AI_TO_AD** dient der Konvertierung eines INT-basierten Adapter-Interface (AI) in ein DWORD-basiertes Adapter-Interface (AD). Er kapselt die Typumwandlung von `INT` nach `DWORD` und ermöglicht so die nahtlose Integration unterschiedlicher Adapter-Typen in Steuerungsanwendungen. Der Baustein ist unidirektional ausgelegt und arbeitet ereignisgesteuert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine direkten Ereignis-Eingänge. Die ereignisgesteuerte Auslösung erfolgt über den Adapter **AI_IN** (Socket).  
- **E1 (über AI_IN)**: Auslöseereignis zur Konvertierung des anliegenden INTEGER-Wertes.

### **Ereignis-Ausgänge**
Der Baustein besitzt keine direkten Ereignis-Ausgänge. Die Bestätigung der Konvertierung erfolgt über den Adapter **AD_OUT** (Plug).  
- **E1 (über AD_OUT)**: Bestätigungsereignis nach erfolgreicher Umwandlung.

### **Daten-Eingänge**
Der Baustein besitzt keine direkten Daten-Eingänge. Der zu konvertierende INTEGER-Wert wird über den Adapter **AI_IN** bereitgestellt.  
- **D1 (über AI_IN)**: Eingangswert vom Typ `INT`.

### **Daten-Ausgänge**
Der Baustein besitzt keine direkten Daten-Ausgänge. Der konvertierte DWORD-Wert wird über den Adapter **AD_OUT** ausgegeben.  
- **D1 (über AD_OUT)**: Ausgangswert vom Typ `DWORD`.

### **Adapter**
- **AI_IN** (Socket) – Eingangsadapter vom Typ `adapter::types::unidirectional::AI`. Er stellt einen INTEGER-Eingang (D1) sowie ein Auslöseereignis (E1) bereit.
- **AD_OUT** (Plug) – Ausgangsadapter vom Typ `adapter::types::unidirectional::AD`. Er stellt einen DWORD-Ausgang (D1) sowie ein Bestätigungsereignis (E1) bereit.

## Funktionsweise
Der Baustein ist als Composite ausgeführt. Intern wird der IEC‑61131-konforme Funktionsbaustein **F_INT_TO_DWORD** verwendet.  
Der Ablauf:
1. Ein Ereignis am Eingangsadapter **AI_IN.E1** löst die Datenübernahme aus.
2. Der Wert von **AI_IN.D1** (INT) wird an den Eingang `IN` von `F_INT_TO_DWORD` weitergeleitet.
3. Der interne Baustein führt die Typkonvertierung `INT → DWORD` durch.
4. Das Ergebnis liegt am Ausgang `OUT` von `F_INT_TO_DWORD` an und wird an **AD_OUT.D1** übergeben.
5. Gleichzeitig wird das Ereignis **AD_OUT.E1** ausgelöst, um die Verarbeitung im nachfolgenden Netzwerk zu signalisieren.

## Technische Besonderheiten
- **Composite‑FB**: Die Funktionalität wird durch einen eingebetteten Baustein realisiert, sodass keine eigene Zustandsmaschine (ECC) erforderlich ist.
- **Unidirektional**: Der Datenfluss erfolgt ausschließlich vom Eingangs- zum Ausgangsadapter; eine Rückkopplung ist nicht vorgesehen.
- **Typkonvertierung**: Der Baustein verwendet den standardisierten IEC‑61131‑Baustein `F_INT_TO_DWORD` und gewährleistet damit Kompatibilität mit vielen Automatisierungssystemen.
- **Adapter‑Kapselung**: Die Konvertierungslogik ist vollständig in die Adapter‑Schnittstellen eingebettet, was die Wiederverwendung in unterschiedlichen Kontexten vereinfacht.

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine. Die interne Verarbeitung wird vollständig durch den eingebetteten Funktionsbaustein `F_INT_TO_DWORD` gesteuert, der eine einfache ereignisgesteuerte Datenverarbeitung ohne Zustände realisiert. Ein Fehlerverhalten oder Timeout sind nicht definiert.

## Anwendungsszenarien
- **Adapter‑Brücke**: Wenn ein Systemkomponente einen INTEGER‑Adapter (AI) bereitstellt, die Zielkomponente jedoch einen DWORD‑Adapter (AD) erwartet.
- **Datenwort‑Erzeugung**: Umrechnung von Analogwerten (z. B. 16‑Bit‑Messwerte) in ein 32‑Bit‑Datenwort für Datenübertragung oder Speicherung.
- **Bibliotheks‑Unabhängigkeit**: Kapselung der Konvertierungsfunktion, sodass Anwendungsentwickler nicht direkt auf IEC‑61131‑Bausteine zugreifen müssen.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_DWORD**: Die direkte IEC‑61131‑Funktion bietet die reine Typumwandlung ohne Adapter‑Einbettung. `AI_TO_AD` fügt die Adapter‑Schnittstellen hinzu und erleichtert so die Integration in adapterbasierte Architekturen.
- **DWORD_TO_INT (umgekehrt)**: Ein entsprechender Baustein für die Rückkonvertierung wäre denkbar, ist aber nicht Teil dieser Implementierung.
- **Eigene Adapter‑Wrapper**: Andere Bausteine könnten ähnliche Konvertierungen für andere Datentypen (z. B. `REAL_TO_DWORD`) bereitstellen.

## Fazit
**AI_TO_AD** ist ein kompakter, adapterorientierter Konvertierungsbaustein, der die Umwandlung von INTEGER- nach DWORD‑Werten nahtlos in bestehende Steuerungsnetzwerke integriert. Durch die Verwendung standardisierter IEC‑61131‑Bausteine und die klare Schnittstellendefinition über Adapter eignet er sich besonders für modulare, wiederverwendbare Automatisierungslösungen.