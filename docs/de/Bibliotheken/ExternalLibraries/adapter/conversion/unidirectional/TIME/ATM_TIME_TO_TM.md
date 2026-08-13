# ATM_TIME_TO_TM

![ATM_TIME_TO_TM](ATM_TIME_TO_TM.svg)

* * * * * * * * * *
## Einleitung

`ATM_TIME_TO_TM` ist ein Composite-Funktionsblock, der einen einfachen `TIME`-Datenwert in das
[ATM](../../../types/unidirectional/TIME/ATM.md)-Adapterformat umwandelt. Er folgt exakt demselben
Muster wie [ADI_DINT_TO_DI](../DINT/ADI_DINT_TO_DI.md) (DINT→ADI) und
[AUI_UINT_TO_UI](../UINT/AUI_UINT_TO_UI.md) (UINT→AUI): eine einzelne Datenverbindung und eine
einzelne Ereignisverbindung, direkt auf den Plug durchgereicht — keine eigene Umrechnungslogik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Anfrage-Event zur Auslösung der Konvertierung; trägt den Wert von `OUT` (`With Var="OUT"`).

### **Ereignis-Ausgänge**

Keine eigenen Ereignis-Ausgänge; das Ereignis läuft ausschließlich über den Adapter-Plug `ATM_OUT`.

### **Daten-Eingänge**

- **OUT** (TIME): Der zu konvertierende Zeitwert.

### **Daten-Ausgänge**

Keine eigenen Daten-Ausgänge; der Wert wird ausschließlich über den Adapter-Plug `ATM_OUT`
bereitgestellt.

### **Adapter**

- **ATM_OUT** (Plug, Typ `adapter::types::unidirectional::ATM`): gibt bei `REQ` den Wert von
  `OUT` über sein `E1`/`D1`-Adapterereignis aus.

## Funktionsweise

Bei Eintreffen des Ereignisses `REQ` wird dieses direkt an `ATM_OUT.E1` weitergereicht, während der
aktuelle Wert von `OUT` gleichzeitig auf `ATM_OUT.D1` gelegt wird. Der Plug `ATM_OUT` feuert damit
sein Adapterereignis mit dem übergebenen Zeitwert — ohne Zwischenspeicherung, ohne
Change-Detection, bei jedem `REQ` erneut.

## Technische Besonderheiten

- **Reine Verdrahtungslogik**, kein eigenes ECC, keine ST-Algorithmen — ein Composite-FB, der
  genau eine Daten- und eine Ereignisverbindung herstellt.
- **Kein `REAL_TO_TIME` in den Standardbibliotheken.** Dieser Baustein wandelt keinen numerischen
  Wert in `TIME` um, sondern nimmt einen bereits fertigen `TIME`-Wert entgegen und reicht ihn nur
  als Adapter weiter. Die eigentliche Umrechnung (z. B. von REAL-Sekunden) erfolgt vorher, typisch
  über `iec61131::arithmetic::F_MULTIME` (`T#1s * REAL#Sekunden`) — siehe den `Override_Timer`-
  Baustein (`adapter::OverrideK`) für ein konkretes Anwendungsbeispiel.
- **Kein Event bei unverändertem Wert wird unterdrückt** — anders als z. B. bei
  [AX_ATM_FB_TON](../../../iec61131-3/timers/AX_ATM_FB_TON.md)s `ET`-Ausgang gibt es hier keine
  `E_D_FF`/`E_D_FF_ANY`-Pufferung; jedes `REQ` erzeugt ein neues Adapterereignis.

## Zustandsübersicht

Der Baustein ist zustandslos: Jedes `REQ`-Ereignis führt unmittelbar zur Ausgabe des aktuellen
`OUT`-Werts über `ATM_OUT`.

## Anwendungsszenarien

- **Sockets füttern, die einen `ATM`-Adapter statt einer einfachen `TIME`-Variable erwarten**, z. B.
  `PT` von [AX_ATM_FB_TON](../../../iec61131-3/timers/AX_ATM_FB_TON.md)/
  [AX_ATM_FB_TOF](../../../iec61131-3/timers/AX_ATM_FB_TOF.md)/
  [AX_ATM_FB_TP](../../../iec61131-3/timers/AX_ATM_FB_TP.md).
- Letztes Glied einer Umrechnungskette von REAL-Sekunden zu einem adapterbasierten Zeitwert
  (`F_MULTIME` → `ATM_TIME_TO_TM`), wie im `Override_Timer`-Baustein (`adapter::OverrideK`).

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[ATM_TM_TO_TIME](ATM_TM_TO_TIME.md)**: die Gegenrichtung — nimmt einen `ATM`-Adapter-Socket
  entgegen und stellt den Wert als einfache `TIME`-Datenvariable bereit.
- **[ADI_DINT_TO_DI](../DINT/ADI_DINT_TO_DI.md) / [AUI_UINT_TO_UI](../UINT/AUI_UINT_TO_UI.md) /
  [AR_REAL_TO_R](../REAL/AR_REAL_TO_R.md)**: dasselbe "Datenwert → Adapter-Plug"-Muster für DINT,
  UINT bzw. REAL statt TIME.

## Fazit

`ATM_TIME_TO_TM` ist die einfachste Möglichkeit, einen `TIME`-Datenwert als `ATM`-Adapter-Plug
bereitzustellen, und schließt damit die Lücke zwischen numerischen Zeitberechnungen (z. B. über
`F_MULTIME`) und adapterbasierten Zeit-Sockets wie `PT` bei `AX_ATM_FB_TON`/`TOF`/`TP`.
