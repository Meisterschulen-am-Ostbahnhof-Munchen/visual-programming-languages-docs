# ATM_TM_TO_TIME

![ATM_TM_TO_TIME](ATM_TM_TO_TIME.svg)

* * * * * * * * * *
## Einleitung

`ATM_TM_TO_TIME` ist die Gegenrichtung zu [ATM_TIME_TO_TM](ATM_TIME_TO_TM.md): ein Composite-
Funktionsblock, der einen [ATM](../../../types/unidirectional/TIME/ATM.md)-Adapter-Socket entgegennimmt
und dessen Wert als einfache `TIME`-Datenvariable bereitstellt. Er folgt exakt demselben Muster wie
[AUI_UI_TO_UINT](../UINT/AUI_UI_TO_UINT.md) (AUI→UINT): eine einzelne Datenverbindung und eine
einzelne Ereignisverbindung, direkt vom Socket abgegriffen — keine eigene Umrechnungslogik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine eigenen Ereignis-Eingänge; das Ereignis kommt ausschließlich über den Adapter-Socket
`ATM_IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigungs-Event, feuert wenn der Adapter-Socket `ATM_IN` sein Ereignis auslöst; trägt
  den Wert von `IN` (`With Var="IN"`).

### **Daten-Eingänge**

Keine eigenen Daten-Eingänge; der Wert kommt ausschließlich über den Adapter-Socket `ATM_IN`.

### **Daten-Ausgänge**

- **IN** (TIME): Der vom Adapter empfangene Zeitwert.

### **Adapter**

- **ATM_IN** (Socket, Typ `adapter::types::unidirectional::ATM`): empfängt den Zeitwert vom
  verbundenen Plug.

## Funktionsweise

Sobald der verbundene Plug ein Ereignis auf `ATM_IN` auslöst, wird `ATM_IN.E1` direkt an `CNF`
weitergereicht, während `ATM_IN.D1` gleichzeitig auf die Datenausgangsvariable `IN` gelegt wird.
Der Baustein macht damit den Wert eines eingehenden `ATM`-Adapters für nachgeschaltete Bausteine
nutzbar, die eine einfache `TIME`-Variable statt eines Adapter-Sockets erwarten (z. B.
`OSCAT::Basic::POUs::conversion::TIME_TO_REAL`, dessen `TM`-Eingang eine reine Datenvariable ist).

## Technische Besonderheiten

- **Reine Verdrahtungslogik**, kein eigenes ECC, keine ST-Algorithmen — ein Composite-FB, der
  genau eine Daten- und eine Ereignisverbindung herstellt.
- **Notwendig, weil Plugs nicht direkt in Funktionen mit einfachen Datenvariablen einspeisen
  können.** Ein Adapter-Plug (z. B. der `ET`-Ausgang von
  [AX_ATM_FB_TON](../../../iec61131-3/timers/AX_ATM_FB_TON.md)) kann nur an einen Socket
  angeschlossen werden, nicht direkt an eine `InputVar` einer Funktion. `ATM_TM_TO_TIME` schließt
  diese Lücke.
- **Kein Event bei unverändertem Wert wird unterdrückt** — der Baustein selbst puffert nichts; ob
  ein Event tatsächlich nur bei Wertänderung kommt, hängt vom vorgeschalteten Plug ab (z. B. hat
  `AX_ATM_FB_TON.ET` bereits eine eigene `E_D_FF_ANY`-Change-Detection).

## Zustandsübersicht

Der Baustein ist zustandslos: Jedes Ereignis am Socket `ATM_IN` führt unmittelbar zur Ausgabe des
aktuellen Werts über `IN`/`CNF`.

## Anwendungsszenarien

- **Einen Adapter-Plug lesbar machen für Funktionen mit einfachen Datenvariablen**, z. B. den
  `ET`-Ausgang von [AX_ATM_FB_TON](../../../iec61131-3/timers/AX_ATM_FB_TON.md)/
  [AX_ATM_FB_TOF](../../../iec61131-3/timers/AX_ATM_FB_TOF.md)/
  [AX_ATM_FB_TP](../../../iec61131-3/timers/AX_ATM_FB_TP.md) an
  `OSCAT::Basic::POUs::conversion::TIME_TO_REAL` weiterreichen.
- Erstes Glied einer Rückrechnungskette von einem adapterbasierten Zeitwert zu REAL-Sekunden
  (`ATM_TM_TO_TIME` → `TIME_TO_REAL` → `F_DIV`), wie im `Override_Timer`-Baustein
  (`adapter::OverrideK`).

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[ATM_TIME_TO_TM](ATM_TIME_TO_TM.md)**: die Gegenrichtung — nimmt eine einfache `TIME`-
  Datenvariable entgegen und stellt sie als `ATM`-Adapter-Plug bereit.
- **[AUI_UI_TO_UINT](../UINT/AUI_UI_TO_UINT.md) / [ADI_DI_TO_DINT](../DINT/ADI_DI_TO_DINT.md)**:
  dasselbe "Adapter-Socket → Datenwert"-Muster für UINT bzw. DINT statt TIME.

## Fazit

`ATM_TM_TO_TIME` ist die einfachste Möglichkeit, den Wert eines `ATM`-Adapter-Plugs als normale
`TIME`-Variable weiterzuverarbeiten, und schließt damit die Lücke zwischen adapterbasierten
Zeit-Plugs (z. B. `ET` bei `AX_ATM_FB_TON`/`TOF`/`TP`) und Funktionen, die nur einfache
Datenvariablen entgegennehmen.
