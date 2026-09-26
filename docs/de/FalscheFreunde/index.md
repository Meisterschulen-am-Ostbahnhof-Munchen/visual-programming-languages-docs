# ⚠️ Falsche Freunde (IEC 61499 / 4diac)

In der ereignisgesteuerten Funktionsbaustein-Programmierung nach **IEC 61499** verhalten sich einige Standard-Bausteine anders, als es Entwickler aus der klassischen zyklischen SPS-Welt (IEC 61131-3) gewohnt sind. Diese Bausteine werden als **„Falsche Freunde“** bezeichnet: Sie tragen vertraute Namen, führen aber ohne Berücksichtigung der Ereignislogik zu subtilen Fehlern, unerwartetem Initialverhalten oder Verklemmungen im System.

Dieses Kapitel dokumentiert typische Fallstricke, erklärt die Ursachen im Event Execution Control Chart (ECC) und zeigt die empfohlenen Abhilfen.

---

## 1. Der `NOT`-Baustein (bzw. `F_NOT`)

### ❌ Das Problem bei `NOT`

In der klassischen SPS-Programmierung (IEC 61131-3) gilt rein statisch: `OUT := NOT IN`. Ist der Eingang `IN = FALSE`, hat der Ausgang `OUT` sofort den Wert `TRUE`.

In **IEC 61499** werden Datenwerte jedoch erst berechnet, wenn ein **Event am `REQ`-Eingang** eintrifft. 
Beim Systemstart / Deployment sind alle Speicherzellen standardmäßig mit Null/`FALSE` belegt:

* `IN = FALSE`
* `OUT = FALSE`

Solange nach dem Start **noch kein erstes Ereignis** an `REQ` empfangen wurde, wird der Rechenalgorithmus nicht ausgeführt. Dadurch befinden sich beim Start **sowohl der Eingang als auch der Ausgang auf `FALSE`**! 
Wird der Ausgang `OUT` direkt zur Freigabe oder Steuerung anderer Bausteine genutzt (z. B. Ruhestromprinzip / Active-Low-Logik), verbleibt das System im uninitialisierten Sperrzustand.

```text
Systemstart / Vor erstem Event:
IN  = FALSE
OUT = FALSE  ❌ (Widerspricht NOT(FALSE) = TRUE)

Nach erstem REQ-Event:
IN  = FALSE
OUT = TRUE   ✅ (Erst jetzt korrekt)
```

### ✅ Abhilfe: `NOT_INIT` bzw. `AX_NOT_INIT` (oder Start-Event-Triggering)

Verwenden Sie bei Signalen, die bereits beim Systemstart einen definierten Zustand erfordern, Bausteine mit explizitem Initialisierungsereignis:

* **`NOT_INIT`** / **`AX_NOT_INIT`**: Diese Bausteine besitzen ein `INIT`-Ereignis (z. B. beim Systemstart durch `E_RESTART` getriggert). Beim Aufruf von `INIT` wird das Signal sofort negiert und der Ausgang mit dem mathematisch korrekten Wert (`TRUE` bei `IN = FALSE`) vorbelegt und ausgegeben.
* **Initiales REQ-Event**: Stellen Sie sicher, dass das erste Ereignis direkt beim Systemstart über ein Initialisierungs-Event gefeuert wird.

---

## 2. Die Bistabilen Elemente `E_RS` und `E_SR`

### ❌ Das Problem bei `E_RS` und `E_SR`

Entwickler erwarten von einem Flip-Flop, dass es in jedem Zustand deterministisch auf Setz- (`S`) und Rücksetz-Signale (`R`) reagiert.

Standard-IEC-61499-Bausteine wie **`E_RS`** und **`E_SR`** beginnen nach dem Deployment im initialen `START`-Zustand ihres Event Execution Control Charts (ECC) mit `Q = FALSE`. In diesem `START`-Zustand existiert gemäß Norm (IEC 61499-1 Tabelle A.1) **ausschließlich eine Zustandstransition für ein `S`-Event (Setzen)**:

* **Eintreffen von `S`**: Der Baustein wechselt in den Zustand `SET`, setzt `Q := TRUE` und sendet `EO`.
* **Eintreffen von `R` im `START`-Zustand**: Trifft als erstes Ereignis nach dem Systemstart ein **`R`-Event (Reset)** ein, gibt es im `START`-Zustand keine passende Transition. Der Baustein verbleibt im `START`-Zustand (`Q` bleibt `FALSE`), jedoch wird **kein `EO`-Ausgangsereignis** generiert.

Falls nachgelagerte Logikbausteine auf eine explizite Bestätigung (`EO`) beim Reset angewiesen sind, verharrt die Ereigniskette im ungetriggerten Zustand.

```text
START-Zustand (nach Deployment, Q = FALSE):
Empfang von 'S' ──► Zustand SET (Q := TRUE, sendet EO)      ✅
Empfang von 'R' ──► Kein Übergang (Q bleibt FALSE, kein EO)  ❌
```

### ✅ Abhilfe: `E_RS_SYM` und `E_SR_SYM` (bzw. `E_RS_SYM_INIT`)

Verwenden Sie stattdessen die **symmetrischen Varianten** (*Symmetric Start-up Behavior*):

* **`E_RS_SYM` / `E_SR_SYM`**: Bereits im initialen `START`-Zustand führen **sowohl `S` als auch `R`** in klar definierte Folgezustände (`SET` bzw. `RESET`). Ein eintreffendes Reset-Event beim Start versetzt den Baustein sofort sauber in den Zustand `RESET` (`Q := FALSE`) und bestätigt dies über `EO`.
* **`E_RS_SYM_INIT` / `E_SR_SYM_INIT`**: Bieten zusätzlich eine gezielte Startwert-Initialisierung über ein `INIT`-Ereignis und den Dateneingang `Q_INIT`.

---

## 3. Übersicht & Empfehlungen

| Baustein | "Falscher Freund" wegen | Empfohlene Alternative / Abhilfe |
| :--- | :--- | :--- |
| **`NOT` / `F_NOT`** | Vor dem ersten `REQ`-Event sind Eingang und Ausgang `FALSE`. | **`NOT_INIT`**, **`AX_NOT_INIT`** oder gezieltes Start-Event-Triggering |
| **`E_RS` / `E_SR`** | Nur ein `S`-Event macht den Baustein aus dem `START`-Zustand betriebsfähig; `R` beim Start wird ignoriert. | **`E_RS_SYM`**, **`E_SR_SYM`** oder **`E_RS_SYM_INIT`** |

---

## 🔮 Ausblick und weitere Themen

Die Liste der „Falsche Freunde“ wird kontinuierlich um weitere Praxis-Fallstricke der ereignisgesteuerten Programmierung erweitert (z. B. unverdrahtete Event-Ausgänge, flanken- vs. pegelgesteuerte Abfragen, Zeitverhalten ohne Zyklusgarantie).
