# UDINT_AUI_EQ


![UDINT_AUI_EQ](./UDINT_AUI_EQ.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **UDINT_AUI_EQ** dient dem Vergleich zweier Werte auf Gleichheit. Er ist als generischer Vergleichsbaustein ausgelegt, der zwei Eingangswerte über einen Socket-Adapter (IN2) und einen direkten Daten-Eingang (IN1) entgegennimmt und das Ergebnis über einen Plug-Adapter (OUT) ausgibt. Der Name deutet auf eine ursprüngliche Verwendung mit ganzzahligen Datentypen (UDINT) hin, die tatsächliche Implementierung arbeitet jedoch mit dem allgemeinen Typ `ANY_ELEMENTARY`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Mit Variablen | Kommentar |
|------|-----|---------------|-----------|
| REQ  | Event | IN1 | Dient als Auslöser für den Vergleich. Der Wert von IN1 wird bei einem Ereignis am REQ-Eingang verarbeitet. |

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden. Das Ergebnis wird über den Adapter-Ausgang (OUT) signalisiert.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| IN1  | ANY_ELEMENTARY | Erster zu vergleichender Wert. Der Datentyp kann jeder elementare Typ (z. B. BOOL, INT, REAL, UDINT) sein. |

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Das Vergleichsergebnis wird über den Adapter-Ausgang (OUT) bereitgestellt.

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| IN2  | adapter::types::unidirectional::AUI | Socket (Eingang) | Zweiter zu vergleichender Wert; wird über den Adapter als Ereignis und Datenwert bereitgestellt. |
| OUT  | adapter::types::unidirectional::AX   | Plug (Ausgang) | Gibt das Ergebnis des Vergleichs (TRUE bei Gleichheit, sonst FALSE) als Ereignis und Datenwert aus. |

## Funktionsweise

Der Baustein führt einen Gleichheitsvergleich zwischen den an IN1 und über den Adapter IN2 gelieferten Werten durch. Die Verarbeitung läuft wie folgt ab:

1. Ein Ereignis kann entweder direkt am **REQ**-Eingang oder über den **IN2**-Adapter (dessen Ereignis-Eingang „E1“) eingehen. Beide Ereignisse werden intern auf den Eingang des Vergleichsbausteins **F_EQ** geführt.
2. Gleichzeitig werden die Datenwerte von **IN1** und **IN2.D1** an die entsprechenden Eingänge von **F_EQ** übergeben.
3. Der interne Baustein **F_EQ** (Typ *iec61131::comparison::F_EQ*) führt den eigentlichen Vergleich durch und gibt das Boolesche Ergebnis an seinem Ausgang **OUT** aus.
4. Dieses Ergebnis wird an den **OUT**-Adapter weitergeleitet, der sowohl das Ereignis **E1** als auch den Datenwert **D1** an die nachfolgende Logik übergibt.

Der Baustein arbeitet rein ereignisgesteuert – ein Vergleich wird nur bei einem eingehenden Ereignis ausgeführt.

## Technische Besonderheiten

- **Generischer Datentyp**: Der Eingang IN1 ist als `ANY_ELEMENTARY` deklariert, sodass der Baustein mit fast allen elementaren Datentypen (BOOL, BYTE, WORD, DWORD, SINT, INT, DINT, LINT, USINT, UINT, UDINT, ULINT, REAL, LREAL) arbeiten kann.
- **Adapterbasierte Schnittstelle**: Statt klassischer Ein-/Ausgänge werden Adapter (Socket/Plug) verwendet. Dies ermöglicht eine flexible Kopplung an andere Bausteine mit kompatiblen Adaptertypen.
- **Kein Zustandsautomat**: Der FB besitzt kein eigenes ECC (Execution Control Chart), sondern realisiert seine Funktionalität rein über das enthaltene Subnetzwerk mit dem Baustein F_EQ.
- **Ereignisweitergabe**: Sowohl das Ereignis von REQ als auch das von IN2 werden auf den gleichen internen REQ-Eingang von F_EQ geführt. Dies kann bei parallelen Ereignissen zu Konflikten führen (letztes Ereignis gewinnt), was bei der Anwendung zu beachten ist.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten endlichen Zustandsautomaten. Sein Verhalten entspricht dem des enthaltenen F_EQ-Bausteins, der als reine Funktion ohne Zustandsspeicher arbeitet.

## Anwendungsszenarien

- **Vergleich von Sensordaten**: Ein Messwert (IN1) wird mit einem Referenzwert (über IN2) verglichen, um Gleichheit festzustellen (z. B. für Grenzwertüberwachung).
- **Identitätsprüfung**: In der Steuerungstechnik kann geprüft werden, ob zwei Eingangssignale identisch sind, bevor eine Aktion ausgelöst wird.
- **Adapterbasierte Architekturen**: Einsatz in modularen Systemen, bei denen Daten über standardisierte Adapter ausgetauscht werden sollen (z. B. in IEC 61499-basierten verteilten Systemen).

## Vergleich mit ähnlichen Bausteinen

- **IEC 61131 EQ**: Der Standard-Gleichheitsbaustein (z. B. `EQ` in IEC 61131) besitzt klassische Ein-/Ausgänge ohne Adapter. *UDINT_AUI_EQ* kapselt die EQ-Funktionalität und fügt eine adapterbasierte Schnittstelle hinzu.
- **Direkter F_EQ**: Der interne Baustein *F_EQ* arbeitet ebenfalls auf gleicher Vergleichslogik, erwartet aber beide Werte an seinen Daten-Eingängen und gibt einen Booleschen Wert direkt aus. *UDINT_AUI_EQ* erweitert dies um eine getrennte Ereignissteuerung über Adapter.
- **Ungleichheit-Vergleiche**: Verwandle Bausteine wie `NE`, `GT`, `LT` nutzen ähnliche Strukturen, unterscheiden sich aber im Vergleichsoperator.

## Fazit

Der **UDINT_AUI_EQ** ist ein nützlicher Baustein für Gleichheitsvergleiche in Umgebungen, die auf Adapterkommunikation setzen. Durch seinen generischen Datentyp eignet er sich für viele Anwendungen, während die adapterbasierte Schnittstelle eine saubere Trennung von Ereignis- und Datenfluss ermöglicht. Der Verzicht auf einen eigenen Zustandsautomaten hält die Implementierung einfach und effizient. Bei der Verwendung sollten die möglichen Ereigniskonflikte durch doppelte Ereignissignalisierung beachtet werden.