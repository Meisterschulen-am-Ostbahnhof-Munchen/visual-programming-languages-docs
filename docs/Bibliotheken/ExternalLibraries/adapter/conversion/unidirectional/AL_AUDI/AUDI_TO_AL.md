# AUDI_TO_AL


![AUDI_TO_AL](./AUDI_TO_AL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUDI_TO_AL** ist ein zusammengesetzter (Composite) Baustein, der die Konvertierung eines **AUDI**-Adapters (Datenformat UDINT) in einen **AL**-Adapter (Datenformat LWORD) realisiert. Er dient als Schnittstellenwandler zwischen unterschiedlichen Adaptertypen in Automatisierungssystemen, die auf dem Standard IEC 61499 basieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine eigenen Ereignis-Eingänge. Die ereignisgesteuerte Verarbeitung erfolgt über den **AUDI_IN**-Socket:  
- **E1** : Ereignisseingang des AUDI-Adapters – löst die Konvertierung aus.

### **Ereignis-Ausgänge**

Der Baustein besitzt keine eigenen Ereignis-Ausgänge. Die Ergebnisweitergabe erfolgt über den **AL_OUT**-Plug:  
- **E1** : Ereignisausgang des AL-Adapters – signalisiert abgeschlossene Konvertierung.

### **Daten-Eingänge**

Der Baustein besitzt keine eigenen Daten-Eingänge. Die zu konvertierenden Daten werden über den **AUDI_IN**-Socket bereitgestellt:  
- **D1** : Dateneingang des AUDI-Adapters (Typ: UDINT) – der zu konvertierende Wert.

### **Daten-Ausgänge**

Der Baustein besitzt keine eigenen Daten-Ausgänge. Das konvertierte Ergebnis wird über den **AL_OUT**-Plug bereitgestellt:  
- **D1** : Datenausgang des AL-Adapters (Typ: LWORD) – der konvertierte Wert.

### **Adapter**

| Name    | Richtung | Typ                                          | Beschreibung                                      |
|---------|----------|----------------------------------------------|---------------------------------------------------|
| AUDI_IN | Socket   | `adapter::types::unidirectional::AUDI`       | UDINT-Adapter als Eingangsschnittstelle           |
| AL_OUT  | Plug     | `adapter::types::unidirectional::AL`         | LWORD-Adapter als Ausgangsschnittstelle           |

## Funktionsweise

Der Baustein bildet eine reine Kapselung der IEC‑61131‑Funktion `F_UDINT_TO_LWORD`.  
Bei einem Ereignis am **AUDI_IN.E1** wird der interne Funktionsbaustein **Convert** (Typ `F_UDINT_TO_LWORD`) über dessen Ereigniseingang **REQ** aktiviert. Gleichzeitig wird der an **AUDI_IN.D1** anliegende UDINT-Wert an den Dateneingang **IN** von **Convert** übergeben. Nach Abschluss der Konvertierung signalisiert **Convert** über seinen Ereignisausgang **CNF** die Fertigstellung. Dieses Ereignis wird direkt an **AL_OUT.E1** weitergeleitet, und der konvertierte LWORD-Wert wird von **Convert.OUT** auf **AL_OUT.D1** ausgegeben.

Der gesamte Ablauf ist ereignisgesteuert und ohne zusätzliche Laufzeitlogik innerhalb des Composite-Bausteins.

## Technische Besonderheiten

- Der Baustein ist als **Composite-Funktionsblock** realisiert und verwendet ausschließlich die standardisierte IEC‑61131‑Konvertierungsfunktion `F_UDINT_TO_LWORD`.
- Die Konvertierung erfolgt direkt: **UDINT** (32‑Bit unsigned integer) wird auf **LWORD** (64‑Bit logical word) abgebildet.  
  Hinweis: Bei der Umwandlung eines 32‑Bit‑Werts in ein 64‑Bit‑Wort werden die oberen 32 Bits auf Null gesetzt.
- Der Baustein ist unter der **Eclipse Public License 2.0** lizenziert.
- Die Schnittstellen (Adapter) sind unidirektional ausgelegt: Der Datenfluss erfolgt nur vom Socket zum Plug.

## Zustandsübersicht

Da es sich um einen zusammengesetzten Baustein ohne eigene Zustandsmaschine handelt, besitzt **AUDI_TO_AL** keinen internen Zustandsautomaten. Das Verhalten wird vollständig durch den verschalteten Funktionbaustein `F_UDINT_TO_LWORD` bestimmt, der einen einfachen REQ/CNF‑Handshake implementiert.

## Anwendungsszenarien

- **Adapter-Konvertierung** in IEC‑61499‑Systemen, in denen ein existierender AUDI‑Adapter (UDINT‑basiert) mit einem AL‑Adapter (LWORD‑basiert) verbunden werden muss – z. B. zur Anbindung von Sensordaten an eine 64‑Bit‑Datenverarbeitungskette.
- **Schnittstellenanpassung** beim Austausch von Hardwarekomponenten oder bei der Migration von 32‑Bit‑ auf 64‑Bit‑Automatisierungslösungen.
- **Prototypische Umsetzung** in der Landtechnik oder anderen Bereichen, in denen die Datenformate UDINT und LWORD gemischt auftreten.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu generischen Konvertern wie `UDINT_TO_LWORD` (einem atomaren Baustein) bietet **AUDI_TO_AL** eine vorgefertigte Adapter‑Kopplung, die den Entwickler von der manuellen Verschaltung von Ereignis- und Datenleitungen befreit. Ähnliche Composite-Bausteine existieren z. B. für `UDINT_TO_DWORD` oder `LREAL_TO_LWORD`, jedoch spezifisch für andere Zieladapter.

## Fazit

Der Funktionsblock **AUDI_TO_AL** ist ein kompakter, wiederverwendbarer Baustein zur sauberen Trennung von Adaptertypen. Durch die Kapselung der Konvertierung in einem Composite vereinfacht er die Wartbarkeit und Lesbarkeit von Anwendungen, die auf unterschiedlichen Datenformatadaptern basieren.